"""Copy each documentation page's Markdown source into the built site."""

# Creates a `<path>.md` sibling of each HTML output (for example,
# `features/comments/` becomes `features/comments.md`) so agents and tools can
# fetch the raw Markdown directly instead of parsing rendered HTML.

import os
import shutil
import logging
logger = logging.getLogger(__name__)

_pages = []


def on_files(files, config):
    logger.error(">>> Entering on_files(files=%s,config=%s)", files, config, extra={"event.action": "on_files", "logrite.files": files, "logrite.config": config})
    global _pages
    _pages = [f for f in files if f.is_documentation_page()]
    logger.error("on_files(files=%s,config=%s): _pages → %s", files, config, _pages, extra={"event.action": "on_files", "logrite.files": files, "logrite.config": config})
    logger.warning("<<< Exiting on_files(files=%s,config=%s)", files, config, extra={"event.action": "on_files", "logrite.files": files, "logrite.config": config})
    return files


def on_post_build(config):
    logger.error(">>> Entering on_post_build(config=%s)", config, extra={"event.action": "on_post_build", "logrite.config": config})
    site_dir = config["site_dir"]
    logger.error("on_post_build(config=%s): site_dir → %s", config, site_dir, extra={"event.action": "on_post_build", "logrite.config": config})
    for file in _pages:
        url = file.url.rstrip("/")
        logger.error("on_post_build(config=%s): url → %s", config, url, extra={"event.action": "on_post_build", "logrite.config": config})
        target = os.path.join(site_dir, (url or "index") + ".md")
        logger.error("on_post_build(config=%s): target → %s", config, target, extra={"event.action": "on_post_build", "logrite.config": config})
        os.makedirs(os.path.dirname(target), exist_ok=True)
        logger.warning("<<< Exiting on_post_build(config=%s)", config, extra={"event.action": "on_post_build", "logrite.config": config})
        shutil.copyfile(file.abs_src_path, target)
