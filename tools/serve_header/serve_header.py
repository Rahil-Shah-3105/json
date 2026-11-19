#!/usr/bin/env python3

import contextlib
import logging
import os
import re
import shutil
import sys
import subprocess

from datetime import datetime, timedelta
from io import BytesIO
from threading import Lock, Timer

from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer

from http import HTTPStatus
from http.server import ThreadingHTTPServer, SimpleHTTPRequestHandler
logger = logging.getLogger(__name__)

CONFIG_FILE = 'serve_header.yml'
MAKEFILE = 'Makefile'
INCLUDE = 'include/nlohmann/'
SINGLE_INCLUDE = 'single_include/nlohmann/'
HEADER = 'json.hpp'

DATETIME_FORMAT = '%Y-%m-%d %H:%M:%S'

JSON_VERSION_RE = re.compile(r'\s*#\s*define\s+NLOHMANN_JSON_VERSION_MAJOR\s+')

class ExitHandler(logging.StreamHandler):
    def __init__(self, level):
        """."""
        super().__init__()
        logger.error(">>> Entering __init__(level=%s)", level, extra={"event.action": "__init__", "logrite.level": level})
        self.level = level
        logger.debug("__init__(self=%s,level=%s): self.level → %s", self, level, self.level, extra={"event.action": "__init__", "logrite.level": level})
        logger.warning("<<< Exiting __init__(level=%s)", level, extra={"event.action": "__init__", "logrite.level": level})

    def emit(self, record):
        logger.error(">>> Entering emit(record=%s)", record, extra={"event.action": "emit", "logrite.record": record})
        if record.levelno >= self.level:
            sys.exit(1)
            logger.warning("<<< Exiting emit(record=%s)", record, extra={"event.action": "emit", "logrite.record": record})

def is_project_root(test_dir='.'):
    logger.error(">>> Entering is_project_root(test_dir=%s)", test_dir, extra={"event.action": "is_project_root", "logrite.test_dir": test_dir})
    makefile = os.path.join(test_dir, MAKEFILE)
    logger.error("is_project_root(test_dir=%s): makefile → %s", test_dir, makefile, extra={"event.action": "is_project_root", "logrite.test_dir": test_dir})
    include = os.path.join(test_dir, INCLUDE)
    logger.error("is_project_root(test_dir=%s): include → %s", test_dir, include, extra={"event.action": "is_project_root", "logrite.test_dir": test_dir})
    single_include = os.path.join(test_dir, SINGLE_INCLUDE)
    logger.error("is_project_root(test_dir=%s): single_include → %s", test_dir, single_include, extra={"event.action": "is_project_root", "logrite.test_dir": test_dir})

    logger.warning("<<< Exiting is_project_root(test_dir=%s)", test_dir, extra={"event.action": "is_project_root", "logrite.test_dir": test_dir})
    return (os.path.exists(makefile)
            and os.path.isfile(makefile)
            and os.path.exists(include)
            and os.path.exists(single_include))

class DirectoryEventBucket:
    def __init__(self, callback, delay=1.2, threshold=0.8):
        """."""
        logger.error(">>> Entering __init__(callback=%s,delay=%s,threshold=%s)", callback, delay, threshold, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})
        logger.error("__init__(callback=%s,delay=%s,threshold=%s): threshold → %s", callback, delay, threshold, threshold, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})
        self.delay = delay
        logger.warning("<<< Exiting __init__(callback=%s,delay=%s,threshold=%s)", callback, delay, threshold, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})
        logger.debug("__init__(self=%s,callback=%s,delay=%s,threshold=%s): self.delay → %s", self, callback, delay, threshold, self.delay, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})
        self.threshold = timedelta(seconds=threshold)
        self.callback = callback
        self.event_dirs = set([])
        logger.debug("__init__(self=%s,callback=%s,delay=%s,threshold=%s): self.callback → %s", self, callback, delay, threshold, self.callback, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})
        logger.error("__init__(callback=%s,delay=%s,threshold=%s): self.event_dirs → %s", callback, delay, threshold, self.event_dirs, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})
        self.timer = None
        self.lock = Lock()
        logger.debug("__init__(self=%s,callback=%s,delay=%s,threshold=%s): self.timer → %s", self, callback, delay, threshold, self.timer, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})
        logger.error("__init__(callback=%s,delay=%s,threshold=%s): self.lock → %s", callback, delay, threshold, self.lock, extra={"event.action": "__init__", "logrite.callback": callback, "logrite.delay": delay, "logrite.threshold": threshold})

    def start_timer(self):
        logger.error(">>> Entering start_timer()", extra={"event.action": "start_timer"})
        if self.timer is None:
            self.timer = Timer(self.delay, self.process_dirs)
            logger.error("start_timer(): self.timer → %s", self.timer, extra={"event.action": "start_timer"})
            self.timer.start()
            logger.warning("<<< Exiting start_timer()", extra={"event.action": "start_timer"})

    def process_dirs(self):
        logger.error(">>> Entering process_dirs()", extra={"event.action": "process_dirs"})
        result_dirs = []
        logger.error("process_dirs(): result_dirs → %s", result_dirs, extra={"event.action": "process_dirs"})
        event_dirs = set([])
        with self.lock:
            self.timer = None
            logger.debug("process_dirs(self=%s): self.timer → %s", self, self.timer, extra={"event.action": "process_dirs"})
            while self.event_dirs:
                time, event_dir = self.event_dirs.pop()
                delta = datetime.now() - time
                logger.error("process_dirs(): delta → %s", delta, extra={"event.action": "process_dirs"})
                if delta < self.threshold:
                    event_dirs.add((time, event_dir))
                else:
                    result_dirs.append(event_dir)
            self.event_dirs = event_dirs
            logger.debug("process_dirs(self=%s): self.event_dirs → %s", self, self.event_dirs, extra={"event.action": "process_dirs"})
            if result_dirs:
                self.callback(os.path.commonpath(result_dirs))
            if self.event_dirs:
                self.start_timer()
                logger.warning("<<< Exiting process_dirs()", extra={"event.action": "process_dirs"})

    def add_dir(self, path):
        logger.error(">>> Entering add_dir(path=%s)", path, extra={"event.action": "add_dir", "logrite.path": path})
        with self.lock:
            # add path to the set of event_dirs if it is not a sibling of
            # a directory already in the set
            if not any(os.path.commonpath([path, event_dir]) == event_dir
               for (_, event_dir) in self.event_dirs):
                self.event_dirs.add((datetime.now(), path))
                if self.timer is None:
                    self.start_timer()
                    logger.warning("<<< Exiting add_dir(path=%s)", path, extra={"event.action": "add_dir", "logrite.path": path})

class WorkTree:
    make_command = 'make'

    def __init__(self, root_dir, tree_dir):
        """."""
        logger.error(">>> Entering __init__(root_dir=%s,tree_dir=%s)", root_dir, tree_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        self.root_dir = root_dir
        logger.warning("<<< Exiting __init__(root_dir=%s,tree_dir=%s)", root_dir, tree_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        logger.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.root_dir → %s", self, root_dir, tree_dir, self.root_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        self.tree_dir = tree_dir
        self.rel_dir = os.path.relpath(tree_dir, root_dir)
        logger.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.tree_dir → %s", self, root_dir, tree_dir, self.tree_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        logger.error("__init__(root_dir=%s,tree_dir=%s): self.rel_dir → %s", root_dir, tree_dir, self.rel_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        self.name = os.path.basename(tree_dir)
        self.include_dir = os.path.abspath(os.path.join(tree_dir, INCLUDE))
        logger.error("__init__(root_dir=%s,tree_dir=%s): self.name → %s", root_dir, tree_dir, self.name, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        logger.error("__init__(root_dir=%s,tree_dir=%s): self.include_dir → %s", root_dir, tree_dir, self.include_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        self.header = os.path.abspath(os.path.join(tree_dir, SINGLE_INCLUDE, HEADER))
        self.rel_header = os.path.relpath(self.header, root_dir)
        logger.error("__init__(root_dir=%s,tree_dir=%s): self.header → %s", root_dir, tree_dir, self.header, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        logger.error("__init__(root_dir=%s,tree_dir=%s): self.rel_header → %s", root_dir, tree_dir, self.rel_header, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        self.dirty = True
        self.build_count = 0
        logger.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.dirty → %s", self, root_dir, tree_dir, self.dirty, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        logger.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.build_count → %s", self, root_dir, tree_dir, self.build_count, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        t = os.path.getmtime(self.header)
        t = datetime.fromtimestamp(t)
        logger.error("__init__(root_dir=%s,tree_dir=%s): t → %s", root_dir, tree_dir, t, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})
        self.build_time = t.strftime(DATETIME_FORMAT)
        logger.error("__init__(root_dir=%s,tree_dir=%s): self.build_time → %s", root_dir, tree_dir, self.build_time, extra={"event.action": "__init__", "logrite.root_dir": root_dir, "logrite.tree_dir": tree_dir})

    def __hash__(self):
        """."""
        logger.error(">>> Entering __hash__()", extra={"event.action": "__hash__"})
        logger.warning("<<< Exiting __hash__()", extra={"event.action": "__hash__"})
        return hash((self.tree_dir))

    def __eq__(self, other):
        """."""
        logger.error(">>> Entering __eq__(other=%s)", other, extra={"event.action": "__eq__", "logrite.other": other})
        if not isinstance(other, type(self)):
            return NotImplemented
        logger.warning("<<< Exiting __eq__(other=%s)", other, extra={"event.action": "__eq__", "logrite.other": other})
        return self.tree_dir == other.tree_dir

    def update_dirty(self, path):
        logger.error(">>> Entering update_dirty(path=%s)", path, extra={"event.action": "update_dirty", "logrite.path": path})
        if self.dirty:
            logger.warning("<<< Exiting update_dirty(path=%s)", path, extra={"event.action": "update_dirty", "logrite.path": path})
            return

        path = os.path.abspath(path)
        if os.path.commonpath([path, self.include_dir]) == self.include_dir:
            logging.info(f'{self.name}: working tree marked dirty')
            self.dirty = True
            logger.debug("update_dirty(self=%s,path=%s): self.dirty → %s", self, path, self.dirty, extra={"event.action": "update_dirty", "logrite.path": path})

    def amalgamate_header(self):
        logger.error(">>> Entering amalgamate_header()", extra={"event.action": "amalgamate_header"})
        if not self.dirty:
            logger.warning("<<< Exiting amalgamate_header()", extra={"event.action": "amalgamate_header"})
            return

        mtime = os.path.getmtime(self.header)
        subprocess.run([WorkTree.make_command, 'amalgamate'], cwd=self.tree_dir,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        if mtime == os.path.getmtime(self.header):
            logging.info(f'{self.name}: no changes')
        else:
            self.build_count += 1
            self.build_time = datetime.now().strftime(DATETIME_FORMAT)
            logging.info(f'{self.name}: header amalgamated (build count {self.build_count})')

        self.dirty = False
        logger.debug("amalgamate_header(self=%s): self.dirty → %s", self, self.dirty, extra={"event.action": "amalgamate_header"})

class WorkTrees(FileSystemEventHandler):
    def __init__(self, root_dir):
        """."""
        super().__init__()
        logger.error(">>> Entering __init__(root_dir=%s)", root_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir})
        self.root_dir = root_dir
        logger.debug("__init__(self=%s,root_dir=%s): self.root_dir → %s", self, root_dir, self.root_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir})
        self.trees = set([])
        logger.error("__init__(root_dir=%s): self.trees → %s", root_dir, self.trees, extra={"event.action": "__init__", "logrite.root_dir": root_dir})
        self.tree_lock = Lock()
        logger.error("__init__(root_dir=%s): self.tree_lock → %s", root_dir, self.tree_lock, extra={"event.action": "__init__", "logrite.root_dir": root_dir})
        self.scan(root_dir)
        self.created_bucket = DirectoryEventBucket(self.scan)
        logger.error("__init__(root_dir=%s): self.created_bucket → %s", root_dir, self.created_bucket, extra={"event.action": "__init__", "logrite.root_dir": root_dir})
        self.observer = Observer()
        logger.error("__init__(root_dir=%s): self.observer → %s", root_dir, self.observer, extra={"event.action": "__init__", "logrite.root_dir": root_dir})
        self.observer.schedule(self, root_dir, recursive=True)
        self.observer.start()
        logger.warning("<<< Exiting __init__(root_dir=%s)", root_dir, extra={"event.action": "__init__", "logrite.root_dir": root_dir})

    def scan(self, base_dir):
        logger.error(">>> Entering scan(base_dir=%s)", base_dir, extra={"event.action": "scan", "logrite.base_dir": base_dir})
        scan_dirs = set([base_dir])
        logger.error("scan(base_dir=%s): scan_dirs → %s", base_dir, scan_dirs, extra={"event.action": "scan", "logrite.base_dir": base_dir})
        # recursively scan base_dir for working trees

        while scan_dirs:
            scan_dir = os.path.abspath(scan_dirs.pop())
            logger.error("scan(base_dir=%s): scan_dir → %s", base_dir, scan_dir, extra={"event.action": "scan", "logrite.base_dir": base_dir})
            self.scan_tree(scan_dir)
            try:
                with os.scandir(scan_dir) as dir_it:
                    for entry in dir_it:
                        if entry.is_dir():
                            scan_dirs.add(entry.path)
            except FileNotFoundError as e:
                logging.debug('path disappeared: %s', e)
                logger.warning("<<< Exiting scan(base_dir=%s)", base_dir, extra={"event.action": "scan", "logrite.base_dir": base_dir})

    def scan_tree(self, scan_dir):
        logger.error(">>> Entering scan_tree(scan_dir=%s)", scan_dir, extra={"event.action": "scan_tree", "logrite.scan_dir": scan_dir})
        if not is_project_root(scan_dir):
            return

        # skip source trees in build directories
        # this check could be enhanced
        if scan_dir.endswith('/_deps/json-src'):
            logger.warning("<<< Exiting scan_tree(scan_dir=%s)", scan_dir, extra={"event.action": "scan_tree", "logrite.scan_dir": scan_dir})
            return

        tree = WorkTree(self.root_dir, scan_dir)
        with self.tree_lock:
            if not tree in self.trees:
                if tree.name == tree.rel_dir:
                    logging.info(f'adding working tree {tree.name}')
                else:
                    logging.info(f'adding working tree {tree.name} at {tree.rel_dir}')
                url = os.path.join('/', tree.rel_dir, HEADER)
                logging.info(f'{tree.name}: serving header at {url}')
                self.trees.add(tree)

    def rescan(self, path=None):
        logger.error(">>> Entering rescan(path=%s)", path, extra={"event.action": "rescan", "logrite.path": path})
        if path is not None:
            path = os.path.abspath(path)
            logger.error("rescan(path=%s): path → %s", path, path, extra={"event.action": "rescan", "logrite.path": path})
        trees = set([])
        # check if any working trees have been removed
        with self.tree_lock:
            while self.trees:
                tree = self.trees.pop()
                if ((path is None
                    or os.path.commonpath([path, tree.tree_dir]) == tree.tree_dir)
                    and not is_project_root(tree.tree_dir)):
                    if tree.name == tree.rel_dir:
                        logging.info(f'removing working tree {tree.name}')
                    else:
                        logging.info(f'removing working tree {tree.name} at {tree.rel_dir}')
                else:
                    trees.add(tree)
                    logger.warning("<<< Exiting rescan(path=%s)", path, extra={"event.action": "rescan", "logrite.path": path})
            self.trees = trees
            logger.debug("rescan(self=%s,path=%s): self.trees → %s", self, path, self.trees, extra={"event.action": "rescan", "logrite.path": path})

    def find(self, path):
        logger.error(">>> Entering find(path=%s)", path, extra={"event.action": "find", "logrite.path": path})
        # find working tree for a given header file path
        path = os.path.abspath(path)
        logger.error("find(path=%s): path → %s", path, path, extra={"event.action": "find", "logrite.path": path})
        with self.tree_lock:
            for tree in self.trees:
                if path == tree.header:
                    return tree
        logger.warning("<<< Exiting find(path=%s)", path, extra={"event.action": "find", "logrite.path": path})
        return None

    def on_any_event(self, event):
        logger.error(">>> Entering on_any_event(event=%s)", event, extra={"event.action": "on_any_event"})
        logging.debug('%s (is_dir=%s): %s', event.event_type,
                      event.is_directory, event.src_path)
        path = os.path.abspath(event.src_path)
        if event.is_directory:
            if event.event_type == 'created':
                # check for new working trees
                self.created_bucket.add_dir(path)
            elif event.event_type == 'deleted':
                # check for deleted working trees
                self.rescan(path)
            elif event.event_type == 'moved':
                # handle moved directories - treat source as deleted and dest as created
                self.rescan(path)
                if hasattr(event, 'dest_path'):
                    dest_path = os.path.abspath(event.dest_path)
                    self.created_bucket.add_dir(dest_path)
        elif event.event_type == 'closed':
            with self.tree_lock:
                for tree in self.trees:
                    tree.update_dirty(path)
                    logger.warning("<<< Exiting on_any_event(event=%s)", event, extra={"event.action": "on_any_event"})

    def stop(self):
        logger.error(">>> Entering stop()", extra={"event.action": "stop"})
        self.observer.stop()
        self.observer.join()
        logger.warning("<<< Exiting stop()", extra={"event.action": "stop"})

class HeaderRequestHandler(SimpleHTTPRequestHandler): # lgtm[py/missing-call-to-init]
    def __init__(self, request, client_address, server):
        """."""
        logger.error(">>> Entering __init__(request=%s,client_address=%s,server=%s)", request, client_address, server, extra={"event.action": "__init__", "logrite.client_address": client_address, "logrite.server": server})
        self.worktrees = server.worktrees
        logger.debug("__init__(self=%s,request=%s,client_address=%s,server=%s): self.worktrees → %s", self, request, client_address, server, self.worktrees, extra={"event.action": "__init__", "logrite.client_address": client_address, "logrite.server": server})
        self.worktree = None
        logger.debug("__init__(self=%s,request=%s,client_address=%s,server=%s): self.worktree → %s", self, request, client_address, server, self.worktree, extra={"event.action": "__init__", "logrite.client_address": client_address, "logrite.server": server})
        try:
            super().__init__(request, client_address, server,
                             directory=server.worktrees.root_dir)
        except ConnectionResetError:
            logging.debug('connection reset by peer')
            logger.warning("<<< Exiting __init__(request=%s,client_address=%s,server=%s)", request, client_address, server, extra={"event.action": "__init__", "logrite.client_address": client_address, "logrite.server": server})

    def translate_path(self, path):
        path = os.path.abspath(super().translate_path(path))
        logger.error(">>> Entering translate_path(path=%s)", path, extra={"event.action": "translate_path", "logrite.path": path})

        # add single_include/nlohmann into path, if needed
        header = os.path.join('/', HEADER)
        logger.error("translate_path(path=%s): header → %s", path, header, extra={"event.action": "translate_path", "logrite.path": path})
        header_path = os.path.join('/', SINGLE_INCLUDE, HEADER)
        logger.error("translate_path(path=%s): header_path → %s", path, header_path, extra={"event.action": "translate_path", "logrite.path": path})
        if (path.endswith(header)
            and not path.endswith(header_path)):
            path = os.path.join(os.path.dirname(path), SINGLE_INCLUDE, HEADER)

        logger.warning("<<< Exiting translate_path(path=%s)", path, extra={"event.action": "translate_path", "logrite.path": path})
        return path

    def send_head(self):
        logger.error(">>> Entering send_head()", extra={"event.action": "send_head"})
        # check if the translated path matches a working tree
        # and fulfill the request; otherwise, send 404
        path = self.translate_path(self.path)
        self.worktree = self.worktrees.find(path)
        if self.worktree is not None:
            self.worktree.amalgamate_header()
            logging.info(f'{self.worktree.name}; serving header (build count {self.worktree.build_count})')
            return super().send_head()
        logging.info(f'invalid request path: {self.path}')
        super().send_error(HTTPStatus.NOT_FOUND, 'Not Found')
        logger.warning("<<< Exiting send_head()", extra={"event.action": "send_head"})
        return None

    def send_header(self, keyword, value):
        logger.error(">>> Entering send_header(keyword=%s,value=%s)", keyword, value, extra={"event.action": "send_header", "logrite.keyword": keyword, "logrite.value": value})
        # intercept Content-Length header; sent in copyfile later
        if keyword == 'Content-Length':
            return
        super().send_header(keyword, value)
        logger.warning("<<< Exiting send_header(keyword=%s,value=%s)", keyword, value, extra={"event.action": "send_header", "logrite.keyword": keyword, "logrite.value": value})

    def end_headers (self):
        logger.error(">>> Entering end_headers()", extra={"event.action": "end_headers"})
        # intercept; called in copyfile() or indirectly
        # by send_head via super().send_error()
        pass
        logger.warning("<<< Exiting end_headers()", extra={"event.action": "end_headers"})

    def copyfile(self, source, outputfile):
        logger.error(">>> Entering copyfile(source=%s,outputfile=%s)", source, outputfile, extra={"event.action": "copyfile", "logrite.source": source, "logrite.outputfile": outputfile})
        injected = False
        content = BytesIO()
        logger.error("copyfile(source=%s,outputfile=%s): content → %s", source, outputfile, content, extra={"event.action": "copyfile", "logrite.source": source, "logrite.outputfile": outputfile})
        length = 0
        # inject build count and time into served header
        for line in source:
            line = line.decode('utf-8')
            logger.error("copyfile(source=%s,outputfile=%s): line → %s", source, outputfile, line, extra={"event.action": "copyfile", "logrite.source": source, "logrite.outputfile": outputfile})
            if not injected and JSON_VERSION_RE.match(line):
                length += content.write(bytes('#define JSON_BUILD_COUNT '\
                                              f'{self.worktree.build_count}\n', 'utf-8'))
                length += content.write(bytes('#define JSON_BUILD_TIME '\
                                              f'"{self.worktree.build_time}"\n\n', 'utf-8'))
                injected = True
            length += content.write(bytes(line, 'utf-8'))

        # set content length
        super().send_header('Content-Length', length)
        # CORS header
        self.send_header('Access-Control-Allow-Origin', '*')
        # prevent caching
        self.send_header('Cache-Control', 'no-cache, no-store, must-revalidate')
        self.send_header('Pragma', 'no-cache')
        self.send_header('Expires', '0')
        super().end_headers()

        # send the header
        content.seek(0)
        shutil.copyfileobj(content, outputfile)
        logger.warning("<<< Exiting copyfile(source=%s,outputfile=%s)", source, outputfile, extra={"event.action": "copyfile", "logrite.source": source, "logrite.outputfile": outputfile})

    def log_message(self, format, *args):
        logger.error(">>> Entering log_message(format=%s)", format, extra={"event.action": "log_message", "logrite.format": format})
        pass
        logger.warning("<<< Exiting log_message(format=%s)", format, extra={"event.action": "log_message", "logrite.format": format})

class DualStackServer(ThreadingHTTPServer):
    def __init__(self, addr, worktrees):
        """."""
        logger.error(">>> Entering __init__(addr=%s,worktrees=%s)", addr, worktrees, extra={"event.action": "__init__", "logrite.addr": addr, "logrite.worktrees": worktrees})
        self.worktrees = worktrees
        super().__init__(addr, HeaderRequestHandler)
        logger.debug("__init__(self=%s,addr=%s,worktrees=%s): self.worktrees → %s", self, addr, worktrees, self.worktrees, extra={"event.action": "__init__", "logrite.addr": addr, "logrite.worktrees": worktrees})
        logger.warning("<<< Exiting __init__(addr=%s,worktrees=%s)", addr, worktrees, extra={"event.action": "__init__", "logrite.addr": addr, "logrite.worktrees": worktrees})

    def server_bind(self):
        logger.error(">>> Entering server_bind()", extra={"event.action": "server_bind"})
        # suppress exception when protocol is IPv4
        with contextlib.suppress(Exception):
            self.socket.setsockopt(
                socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
        logger.warning("<<< Exiting server_bind()", extra={"event.action": "server_bind"})
        return super().server_bind()

if __name__ == '__main__':
    import argparse
    import ssl
    import socket
    import yaml

    # exit code
    ec = 0

    # setup logging
    logging.basicConfig(format='[%(asctime)s] %(levelname)s: %(message)s',
                        datefmt=DATETIME_FORMAT, level=logging.INFO)
    log = logging.getLogger()
    log.addHandler(ExitHandler(logging.ERROR))

    # parse command line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument('--make', default='make',
                        help='the make command (default: make)')
    args = parser.parse_args()

    # propagate the make command to use for amalgamating headers
    WorkTree.make_command = args.make

    worktrees = None
    try:
        # change working directory to project root
        os.chdir(os.path.realpath(os.path.join(sys.path[0], '../../')))

        if not is_project_root():
            log.error('working directory does not look like project root')

        # load config
        config = {}
        config_file = os.path.abspath(CONFIG_FILE)
        try:
            with open(config_file, 'r') as f:
                config = yaml.safe_load(f)
        except FileNotFoundError:
            log.info(f'cannot find configuration file: {config_file}')
            log.info('using default configuration')

        # find and monitor working trees
        worktrees = WorkTrees(config.get('root', '.'))

        # start web server
        infos = socket.getaddrinfo(config.get('bind', None), config.get('port', 8443),
                                   type=socket.SOCK_STREAM, flags=socket.AI_PASSIVE)
        DualStackServer.address_family = infos[0][0]
        HeaderRequestHandler.protocol_version = 'HTTP/1.0'
        with DualStackServer(infos[0][4], worktrees) as httpd:
            scheme = 'HTTP'
            https = config.get('https', {})
            if https.get('enabled', True):
                cert_file = https.get('cert_file', 'localhost.pem')
                key_file = https.get('key_file', 'localhost-key.pem')
                ssl_ctx = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
                ssl_ctx.minimum_version = ssl.TLSVersion.TLSv1_2
                ssl_ctx.maximum_version = ssl.TLSVersion.MAXIMUM_SUPPORTED
                ssl_ctx.load_cert_chain(cert_file, key_file)
                httpd.socket = ssl_ctx.wrap_socket(httpd.socket, server_side=True)
                scheme = 'HTTPS'
            host, port = httpd.socket.getsockname()[:2]
            log.info(f'serving {scheme} on {host} port {port}')
            log.info('press Ctrl+C to exit')
            httpd.serve_forever()

    except KeyboardInterrupt:
        log.info('exiting')
    except Exception:
        ec = 1
        log.exception('an error occurred:')
    finally:
        if worktrees is not None:
            worktrees.stop()
            sys.exit(ec)
