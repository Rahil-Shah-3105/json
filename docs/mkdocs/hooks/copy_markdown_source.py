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
    logger.debug(">>> Entering on_files(files=%s,config=%s)", files, config)
    global _pages
    _pages = [f for f in files if f.is_documentation_page()]
    logger.debug("on_files(files=%s,config=%s): _pages → %s", files, config, _pages)
    logger.debug("<<< Exiting on_files(files=%s,config=%s)", files, config)
    return files


def on_post_build(config):
    logger.debug(">>> Entering on_post_build(config=%s)", config)
    site_dir = config["site_dir"]
    logger.debug("on_post_build(config=%s): site_dir → %s", config, site_dir)
    for file in _pages:
        url = file.url.rstrip("/")
        logger.info("on_post_build(config=%s): url → %s", config, url)
        logger.debug("on_post_build(config=%s): url → %s", config, url)
        target = os.path.join(site_dir, (url or "index") + ".md")
        logger.debug("on_post_build(config=%s): target → %s", config, target)
        os.makedirs(os.path.dirname(target), exist_ok=True)
        logger.debug("<<< Exiting on_post_build(config=%s)", config)
        shutil.copyfile(file.abs_src_path, target)
