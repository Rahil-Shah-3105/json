import gdb
import re
import logging
logger = logging.getLogger(__name__)

ns_pattern = re.compile(r'nlohmann(::json_abi(?P<tags>\w*)(_v(?P<v_major>\d+)_(?P<v_minor>\d+)_(?P<v_patch>\d+))?)?::(?P<name>.+)')
class JsonValuePrinter:
    "Print a json-value"

    def __init__(self, val):
        logger.debug(">>> Entering __init__(val=%s)", val)
        self.val = val
        logger.debug("__init__(self=%s,val=%s): self.val → %s", self, val, self.val)
        logger.debug("<<< Exiting __init__(val=%s)", val)

    def to_string(self):
        logger.debug(">>> Entering to_string()")
        if self.val.type.strip_typedefs().code == gdb.TYPE_CODE_FLT:
            return ("%.6f" % float(self.val)).rstrip("0")
        logger.debug("<<< Exiting to_string()")
        return self.val

def json_lookup_function(val):
    logger.debug(">>> Entering json_lookup_function(val=%s)", val)
    if m := ns_pattern.fullmatch(str(val.type.strip_typedefs().name)):
        name = m.group('name')
        logger.debug("json_lookup_function(val=%s): name → %s", val, name)
        if name and name.startswith('basic_json<') and name.endswith('>'):
            m_data = val['m_data']
            logger.debug("json_lookup_function(val=%s): m_data → %s", val, m_data)
            m_type = m_data['m_type']
            logger.debug("json_lookup_function(val=%s): m_type → %s", val, m_type)
            m = ns_pattern.fullmatch(str(m_type))
            t = m.group('name')
            logger.debug("json_lookup_function(val=%s): m → %s", val, m)
            logger.debug("json_lookup_function(val=%s): t → %s", val, t)
            prefix = 'detail::value_t::'
            logger.debug("json_lookup_function(val=%s): prefix → %s", val, prefix)
            if t and t.startswith(prefix):
                try:
                    union_val = m_data['m_value'][t.replace(prefix, '', 1)]
                    logger.debug("json_lookup_function(val=%s): union_val → %s", val, union_val)
                    if union_val.type.code == gdb.TYPE_CODE_PTR:
                        return gdb.default_visualizer(union_val.dereference())
                    else:
                        return JsonValuePrinter(union_val)
                except Exception:
                    logger.debug("<<< Exiting json_lookup_function(val=%s)", val)
                    return JsonValuePrinter(m_type)

gdb.pretty_printers.append(json_lookup_function)
