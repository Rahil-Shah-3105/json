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
        log.debug(">>> Entering __init__(level=%s)", level)
        self.level = level
        log.debug("__init__(self=%s,level=%s): self.level → %s", self, level, self.level)
        log.debug(">>> Entering __init__(callback=%s,delay=%s,threshold=%s)", callback, delay, threshold)
        log.debug("<<< Exiting __init__(callback=%s,delay=%s,threshold=%s)", callback, delay, threshold)
        log.debug("__init__(self=%s,callback=%s,delay=%s,threshold=%s): self.delay → %s", self, callback, delay, threshold, self.delay)
        log.debug("__init__(callback=%s,delay=%s,threshold=%s): threshold → %s", callback, delay, threshold, threshold)
        log.debug("__init__(self=%s,callback=%s,delay=%s,threshold=%s): self.callback → %s", self, callback, delay, threshold, self.callback)
        log.debug("__init__(callback=%s,delay=%s,threshold=%s): self.event_dirs → %s", callback, delay, threshold, self.event_dirs)
        log.debug("__init__(self=%s,callback=%s,delay=%s,threshold=%s): self.timer → %s", self, callback, delay, threshold, self.timer)

    def emit(self, record):
        log.debug(">>> Entering emit(record=%s)", record)
        if record.levelno >= self.level:
            sys.exit(1)
            log.debug("<<< Exiting emit(record=%s)", record)

def is_project_root(test_dir='.'):
    log.debug(">>> Entering is_project_root(test_dir=%s)", test_dir)
    makefile = os.path.join(test_dir, MAKEFILE)
    log.debug("is_project_root(test_dir=%s): makefile → %s", test_dir, makefile)
    include = os.path.join(test_dir, INCLUDE)
    single_include = os.path.join(test_dir, SINGLE_INCLUDE)
    log.debug("is_project_root(test_dir=%s): include → %s", test_dir, include)

    log.debug("is_project_root(test_dir=%s): single_include → %s", test_dir, single_include)
    log.debug("<<< Exiting is_project_root(test_dir=%s)", test_dir)
    return (os.path.exists(makefile)
            and os.path.isfile(makefile)
            and os.path.exists(include)
            and os.path.exists(single_include))

class DirectoryEventBucket:
    def __init__(self, callback, delay=1.2, threshold=0.8):
        """."""
        self.delay = delay
        self.threshold = timedelta(seconds=threshold)
        self.callback = callback
        self.event_dirs = set([])
        self.timer = None
        self.lock = Lock()
        log.debug("__init__(callback=%s,delay=%s,threshold=%s): self.lock → %s", callback, delay, threshold, self.lock)
        log.debug(">>> Entering __init__(root_dir=%s,tree_dir=%s)", root_dir, tree_dir)
        log.debug("<<< Exiting __init__(root_dir=%s,tree_dir=%s)", root_dir, tree_dir)
        log.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.root_dir → %s", self, root_dir, tree_dir, self.root_dir)
        log.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.tree_dir → %s", self, root_dir, tree_dir, self.tree_dir)
        log.debug("__init__(root_dir=%s,tree_dir=%s): self.rel_dir → %s", root_dir, tree_dir, self.rel_dir)
        log.debug("__init__(root_dir=%s,tree_dir=%s): self.name → %s", root_dir, tree_dir, self.name)
        log.debug("__init__(root_dir=%s,tree_dir=%s): self.include_dir → %s", root_dir, tree_dir, self.include_dir)
        log.debug("__init__(root_dir=%s,tree_dir=%s): self.header → %s", root_dir, tree_dir, self.header)
        log.debug("__init__(root_dir=%s,tree_dir=%s): self.rel_header → %s", root_dir, tree_dir, self.rel_header)
        log.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.dirty → %s", self, root_dir, tree_dir, self.dirty)
        log.debug("__init__(self=%s,root_dir=%s,tree_dir=%s): self.build_count → %s", self, root_dir, tree_dir, self.build_count)
        log.debug("__init__(root_dir=%s,tree_dir=%s): t → %s", root_dir, tree_dir, t)
        log.debug("__init__(root_dir=%s,tree_dir=%s): self.build_time → %s", root_dir, tree_dir, self.build_time)

    def start_timer(self):
        log.debug(">>> Entering start_timer()")
        if self.timer is None:
            self.timer = Timer(self.delay, self.process_dirs)
            log.debug("start_timer(): self.timer → %s", self.timer)
            self.timer.start()
            log.debug("<<< Exiting start_timer()")

    def process_dirs(self):
        log.debug(">>> Entering process_dirs()")
        log.debug("process_dirs(self=%s): self.timer → %s", self, self.timer)
        log.debug("process_dirs(): delta → %s", delta)
        log.debug("process_dirs(self=%s): delta → %s", self, delta)
        result_dirs = []
        log.debug("process_dirs(): result_dirs → %s", result_dirs)
        log.debug("process_dirs(self=%s): result_dirs → %s", self, result_dirs)
        event_dirs = set([])
        log.debug("process_dirs(self=%s): event_dirs → %s", self, event_dirs)
        with self.lock:
            self.timer = None
            log.error("Exception in process_dirs()", exc_info=True)
            while self.event_dirs:
                time, event_dir = self.event_dirs.pop()
                delta = datetime.now() - time
                if delta < self.threshold:
                    event_dirs.add((time, event_dir))
                else:
                    result_dirs.append(event_dir)
            self.event_dirs = event_dirs
            log.debug("process_dirs(self=%s): self.event_dirs → %s", self, self.event_dirs)
            if result_dirs:
                self.callback(os.path.commonpath(result_dirs))
            if self.event_dirs:
                self.start_timer()
                log.debug("<<< Exiting process_dirs()")

    def add_dir(self, path):
        log.debug(">>> Entering add_dir(path=%s)", path)
        with self.lock:
            log.error("Exception in add_dir(path=%s)", path, exc_info=True)
            # add path to the set of event_dirs if it is not a sibling of
            # a directory already in the set
            if not any(os.path.commonpath([path, event_dir]) == event_dir
               for (_, event_dir) in self.event_dirs):
                self.event_dirs.add((datetime.now(), path))
                if self.timer is None:
                    self.start_timer()
                    log.debug("<<< Exiting add_dir(path=%s)", path)

class WorkTree:
    make_command = 'make'

    def __init__(self, root_dir, tree_dir):
        """."""
        self.root_dir = root_dir
        self.tree_dir = tree_dir
        self.rel_dir = os.path.relpath(tree_dir, root_dir)
        self.name = os.path.basename(tree_dir)
        self.include_dir = os.path.abspath(os.path.join(tree_dir, INCLUDE))
        self.header = os.path.abspath(os.path.join(tree_dir, SINGLE_INCLUDE, HEADER))
        self.rel_header = os.path.relpath(self.header, root_dir)
        self.dirty = True
        self.build_count = 0
        t = os.path.getmtime(self.header)
        t = datetime.fromtimestamp(t)
        self.build_time = t.strftime(DATETIME_FORMAT)
        log.debug(">>> Entering __init__(root_dir=%s)", root_dir)
        log.debug("__init__(self=%s,root_dir=%s): self.root_dir → %s", self, root_dir, self.root_dir)
        log.debug("__init__(root_dir=%s): self.trees → %s", root_dir, self.trees)
        log.debug("__init__(root_dir=%s): self.tree_lock → %s", root_dir, self.tree_lock)
        log.debug("__init__(root_dir=%s): self.created_bucket → %s", root_dir, self.created_bucket)
        log.debug("__init__(root_dir=%s): self.observer → %s", root_dir, self.observer)
        log.debug("<<< Exiting __init__(root_dir=%s)", root_dir)

    def __hash__(self):
        """."""
        log.debug(">>> Entering __hash__()")
        log.debug("<<< Exiting __hash__()")
        return hash((self.tree_dir))

    def __eq__(self, other):
        """."""
        log.debug(">>> Entering __eq__(other=%s)", other)
        if not isinstance(other, type(self)):
            return NotImplemented
        log.debug("<<< Exiting __eq__(other=%s)", other)
        return self.tree_dir == other.tree_dir

    def update_dirty(self, path):
        log.debug(">>> Entering update_dirty(path=%s)", path)
        if self.dirty:
            log.debug("<<< Exiting update_dirty(path=%s)", path)
            return

        path = os.path.abspath(path)
        if os.path.commonpath([path, self.include_dir]) == self.include_dir:
            logging.info(f'{self.name}: working tree marked dirty')
            self.dirty = True
            log.debug("update_dirty(self=%s,path=%s): self.dirty → %s", self, path, self.dirty)

    def amalgamate_header(self):
        log.debug(">>> Entering amalgamate_header()")
        if not self.dirty:
            log.debug("<<< Exiting amalgamate_header()")
            return

        mtime = os.path.getmtime(self.header)
        subprocess.run([WorkTree.make_command, 'amalgamate'], cwd=self.tree_dir,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        log.debug("amalgamate_header(self=%s): stdout → %s", self, stdout)
        if mtime == os.path.getmtime(self.header):
            logging.info(f'{self.name}: no changes')
        else:
            self.build_count += 1
            self.build_time = datetime.now().strftime(DATETIME_FORMAT)
            logging.info(f'{self.name}: header amalgamated (build count {self.build_count})')

        self.dirty = False
        log.debug("amalgamate_header(self=%s): self.dirty → %s", self, self.dirty)

class WorkTrees(FileSystemEventHandler):
    def __init__(self, root_dir):
        """."""
        super().__init__()
        self.root_dir = root_dir
        self.trees = set([])
        self.tree_lock = Lock()
        self.scan(root_dir)
        self.created_bucket = DirectoryEventBucket(self.scan)
        self.observer = Observer()
        self.observer.schedule(self, root_dir, recursive=True)
        self.observer.start()
        log.debug(">>> Entering __init__(request=%s,client_address=%s,server=%s)", request, client_address, server)
        log.debug("__init__(self=%s,request=%s,client_address=%s,server=%s): self.worktrees → %s", self, request, client_address, server, self.worktrees)
        log.debug("__init__(self=%s,request=%s,client_address=%s,server=%s): self.worktree → %s", self, request, client_address, server, self.worktree)
        log.debug("__init__(self=%s,request=%s,client_address=%s,server=%s): directory → %s", self, request, client_address, server, directory)
        log.error("Exception in __init__(request=%s,client_address=%s,server=%s)", request, client_address, server, exc_info=True)
        log.debug("<<< Exiting __init__(request=%s,client_address=%s,server=%s)", request, client_address, server)

    def scan(self, base_dir):
        log.debug(">>> Entering scan(base_dir=%s)", base_dir)
        scan_dirs = set([base_dir])
        log.debug("scan(base_dir=%s): scan_dirs → %s", base_dir, scan_dirs)
        log.debug("scan(self=%s,base_dir=%s): scan_dirs → %s", self, base_dir, scan_dirs)
        # recursively scan base_dir for working trees

        while scan_dirs:
            scan_dir = os.path.abspath(scan_dirs.pop())
            log.debug("scan(self=%s,base_dir=%s): scan_dir → %s", self, base_dir, scan_dir)
            log.debug("scan(base_dir=%s): scan_dir → %s", base_dir, scan_dir)
            self.scan_tree(scan_dir)
            try:
                with os.scandir(scan_dir) as dir_it:
                    log.error("Exception in scan(base_dir=%s): %s", base_dir, str(e), exc_info=True)
                    for entry in dir_it:
                        if entry.is_dir():
                            scan_dirs.add(entry.path)
            except FileNotFoundError as e:
                logging.debug('path disappeared: %s', e)
                log.debug("<<< Exiting scan(base_dir=%s)", base_dir)

    def scan_tree(self, scan_dir):
        log.debug(">>> Entering scan_tree(scan_dir=%s)", scan_dir)
        if not is_project_root(scan_dir):
            return

        # skip source trees in build directories
        # this check could be enhanced
        if scan_dir.endswith('/_deps/json-src'):
            log.debug("<<< Exiting scan_tree(scan_dir=%s)", scan_dir)
            return

        tree = WorkTree(self.root_dir, scan_dir)
        log.debug("scan_tree(self=%s,scan_dir=%s): tree → %s", self, scan_dir, tree)
        with self.tree_lock:
            log.error("Exception in scan_tree(scan_dir=%s)", scan_dir, exc_info=True)
            if not tree in self.trees:
                if tree.name == tree.rel_dir:
                    logging.info(f'adding working tree {tree.name}')
                else:
                    logging.info(f'adding working tree {tree.name} at {tree.rel_dir}')
                url = os.path.join('/', tree.rel_dir, HEADER)
                log.info("scan_tree(self=%s,scan_dir=%s): url → %s", self, scan_dir, url)
                logging.info(f'{tree.name}: serving header at {url}')
                self.trees.add(tree)

    def rescan(self, path=None):
        log.debug(">>> Entering rescan(path=%s)", path)
        if path is not None:
            path = os.path.abspath(path)
            log.debug("rescan(path=%s): path → %s", path, path)
        trees = set([])
        log.debug("rescan(self=%s,path=%s): trees → %s", self, path, trees)
        # check if any working trees have been removed
        with self.tree_lock:
            log.error("Exception in rescan(path=%s)", path, exc_info=True)
            log.debug("rescan(path=%s): tree → %s", path, tree)
            log.debug("rescan(self=%s,path=%s): tree → %s", self, path, tree)
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
                    log.debug("<<< Exiting rescan(path=%s)", path)
            self.trees = trees
            log.debug("rescan(self=%s,path=%s): self.trees → %s", self, path, self.trees)

    def find(self, path):
        log.debug(">>> Entering find(path=%s)", path)
        # find working tree for a given header file path
        path = os.path.abspath(path)
        log.debug("find(path=%s): path → %s", path, path)
        with self.tree_lock:
            log.error("Exception in find(path=%s)", path, exc_info=True)
            for tree in self.trees:
                if path == tree.header:
                    return tree
        log.debug("<<< Exiting find(path=%s)", path)
        return None

    def on_any_event(self, event):
        log.debug(">>> Entering on_any_event(event=%s)", event)
        logging.debug('%s (is_dir=%s): %s', event.event_type,
                      event.is_directory, event.src_path)
        path = os.path.abspath(event.src_path)
        log.debug("on_any_event(self=%s,event=%s): path → %s", self, event, path)
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
                    log.debug("on_any_event(self=%s,event=%s): dest_path → %s", self, event, dest_path)
                    log.debug("on_any_event(event=%s): dest_path → %s", event, dest_path)
                    self.created_bucket.add_dir(dest_path)
        elif event.event_type == 'closed':
            with self.tree_lock:
                log.error("Exception in on_any_event(event=%s)", event, exc_info=True)
                for tree in self.trees:
                    tree.update_dirty(path)
                    log.debug("<<< Exiting on_any_event(event=%s)", event)

    def stop(self):
        log.debug(">>> Entering stop()")
        self.observer.stop()
        self.observer.join()
        log.debug("<<< Exiting stop()")

class HeaderRequestHandler(SimpleHTTPRequestHandler): # lgtm[py/missing-call-to-init]
    def __init__(self, request, client_address, server):
        """."""
        self.worktrees = server.worktrees
        self.worktree = None
        try:
            super().__init__(request, client_address, server,
                             directory=server.worktrees.root_dir)
        except ConnectionResetError:
            log.error("Exception in __init__(request=%s,client_address=%s,server=%s)", request, client_address, server, exc_info=True)
            logging.debug('connection reset by peer')
            log.debug("<<< Exiting __init__(request=%s,client_address=%s,server=%s)", request, client_address, server)
            log.debug(">>> Entering __init__(addr=%s,worktrees=%s)", addr, worktrees)
            log.debug("__init__(self=%s,addr=%s,worktrees=%s): self.worktrees → %s", self, addr, worktrees, self.worktrees)
            log.debug("<<< Exiting __init__(addr=%s,worktrees=%s)", addr, worktrees)

    def translate_path(self, path):
        path = os.path.abspath(super().translate_path(path))
        log.debug(">>> Entering translate_path(path=%s)", path)
        log.debug("translate_path(path=%s): path → %s", path, path)
        log.debug("translate_path(path=%s): header_path → %s", path, header_path)
        log.debug("translate_path(path=%s): header → %s", path, header)
        log.debug("translate_path(self=%s,path=%s): header → %s", self, path, header)
        log.debug("translate_path(self=%s,path=%s): header_path → %s", self, path, header_path)

        # add single_include/nlohmann into path, if needed
        header = os.path.join('/', HEADER)
        header_path = os.path.join('/', SINGLE_INCLUDE, HEADER)
        if (path.endswith(header)
            and not path.endswith(header_path)):
            path = os.path.join(os.path.dirname(path), SINGLE_INCLUDE, HEADER)

        log.debug("<<< Exiting translate_path(path=%s)", path)
        return path

    def send_head(self):
        log.debug(">>> Entering send_head()")
        # check if the translated path matches a working tree
        # and fulfill the request; otherwise, send 404
        path = self.translate_path(self.path)
        log.debug("send_head(self=%s): path → %s", self, path)
        self.worktree = self.worktrees.find(path)
        log.debug("send_head(): self.worktree → %s", self.worktree)
        if self.worktree is not None:
            self.worktree.amalgamate_header()
            logging.info(f'{self.worktree.name}; serving header (build count {self.worktree.build_count})')
            return super().send_head()
        logging.info(f'invalid request path: {self.path}')
        super().send_error(HTTPStatus.NOT_FOUND, 'Not Found')
        log.debug("<<< Exiting send_head()")
        return None

    def send_header(self, keyword, value):
        log.debug(">>> Entering send_header(keyword=%s,value=%s)", keyword, value)
        # intercept Content-Length header; sent in copyfile later
        if keyword == 'Content-Length':
            return
        super().send_header(keyword, value)
        log.debug("<<< Exiting send_header(keyword=%s,value=%s)", keyword, value)

    def end_headers (self):
        log.debug(">>> Entering end_headers()")
        # intercept; called in copyfile() or indirectly
        # by send_head via super().send_error()
        pass
        log.debug("<<< Exiting end_headers()")

    def copyfile(self, source, outputfile):
        log.debug(">>> Entering copyfile(source=%s,outputfile=%s)", source, outputfile)
        log.debug("copyfile(source=%s,outputfile=%s): line → %s", source, outputfile, line)
        log.debug("copyfile(self=%s,source=%s,outputfile=%s): line → %s", self, source, outputfile, line)
        injected = False
        log.debug("copyfile(self=%s,source=%s,outputfile=%s): injected → %s", self, source, outputfile, injected)
        content = BytesIO()
        log.debug("copyfile(source=%s,outputfile=%s): content → %s", source, outputfile, content)
        log.debug("copyfile(self=%s,source=%s,outputfile=%s): content → %s", self, source, outputfile, content)
        length = 0
        log.debug("copyfile(self=%s,source=%s,outputfile=%s): length → %s", self, source, outputfile, length)
        # inject build count and time into served header
        for line in source:
            line = line.decode('utf-8')
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
        log.debug("<<< Exiting copyfile(source=%s,outputfile=%s)", source, outputfile)

    def log_message(self, format, *args):
        log.debug(">>> Entering log_message(format=%s)", format)
        pass
        log.debug("<<< Exiting log_message(format=%s)", format)

class DualStackServer(ThreadingHTTPServer):
    def __init__(self, addr, worktrees):
        """."""
        self.worktrees = worktrees
        super().__init__(addr, HeaderRequestHandler)

    def server_bind(self):
        log.debug(">>> Entering server_bind()")
        # suppress exception when protocol is IPv4
        with contextlib.suppress(Exception):
            log.error("Exception in server_bind()", exc_info=True)
            self.socket.setsockopt(
                socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
        log.debug("<<< Exiting server_bind()")
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
