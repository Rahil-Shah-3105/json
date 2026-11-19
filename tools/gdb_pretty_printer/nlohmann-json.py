import gdb
import re
import logging
logger = logging.getLogger(__name__)

ns_pattern = re.compile(r'nlohmann(::json_abi(?P<tags>\w*)(_v(?P<v_major>\d+)_(?P<v_minor>\d+)_(?P<v_patch>\d+))?)?::(?P<name>.+)')
class JsonValuePrinter:
    "Print a json-value"

    def __init__(self, val):
        logger.error(">>> Entering __init__(val=%s)", val, extra={"event.action": "__init__", "logrite.val": val})
        self.val = val
        logger.warning("<<< Exiting __init__(val=%s)", val, extra={"event.action": "__init__", "logrite.val": val})
        logger.debug("__init__(self=%s,val=%s): self.val → %s", self, val, self.val, extra={"event.action": "__init__", "logrite.val": val})

    def to_string(self):
        logger.error(">>> Entering to_string()", extra={"event.action": "to_string"})
        if self.val.type.strip_typedefs().code == gdb.TYPE_CODE_FLT:
            return ("%.6f" % float(self.val)).rstrip("0")
        logger.warning("<<< Exiting to_string()", extra={"event.action": "to_string"})
        return self.val

def json_lookup_function(val):
    logger.error(">>> Entering json_lookup_function(val=%s)", val, extra={"event.action": "json_lookup_function", "logrite.val": val})
    if m := ns_pattern.fullmatch(str(val.type.strip_typedefs().name)):
        name = m.group('name')
        logger.error("json_lookup_function(val=%s): name → %s", val, name, extra={"event.action": "json_lookup_function", "logrite.val": val})
        if name and name.startswith('basic_json<') and name.endswith('>'):
            m_data = val['m_data']
            logger.error("json_lookup_function(val=%s): m_data → %s", val, m_data, extra={"event.action": "json_lookup_function", "logrite.val": val})
            m_type = m_data['m_type']
            logger.error("json_lookup_function(val=%s): m_type → %s", val, m_type, extra={"event.action": "json_lookup_function", "logrite.val": val})
            m = ns_pattern.fullmatch(str(m_type))
            logger.error("json_lookup_function(val=%s): m → %s", val, m, extra={"event.action": "json_lookup_function", "logrite.val": val})
            t = m.group('name')
            logger.error("json_lookup_function(val=%s): t → %s", val, t, extra={"event.action": "json_lookup_function", "logrite.val": val})
            prefix = 'detail::value_t::'
            logger.error("json_lookup_function(val=%s): prefix → %s", val, prefix, extra={"event.action": "json_lookup_function", "logrite.val": val})
            if t and t.startswith(prefix):
                try:
                    union_val = m_data['m_value'][t.replace(prefix, '', 1)]
                    logger.error("json_lookup_function(val=%s): union_val → %s", val, union_val, extra={"event.action": "json_lookup_function", "logrite.val": val})
                    if union_val.type.code == gdb.TYPE_CODE_PTR:
                        return gdb.default_visualizer(union_val.dereference())
                    else:
                        return JsonValuePrinter(union_val)
                except Exception:
                    logger.warning("<<< Exiting json_lookup_function(val=%s)", val, extra={"event.action": "json_lookup_function", "logrite.val": val})
                    return JsonValuePrinter(m_type)

gdb.pretty_printers.append(json_lookup_function)
