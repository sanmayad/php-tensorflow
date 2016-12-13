
#include "tf_session_options.h"

// predefine
zend_class_entry *ce_TF_SessionOptions = NULL;
zend_object_handlers oh_TF_SessionOptions;

// methods
zend_object* tf_session_options_object_create(zend_class_entry* ce TSRMLS_DC);
static void tf_session_options_object_free(zend_object *object TSRMLS_DC);

static PHP_METHOD(TensorFlow_SessionOptions, __construct);
static PHP_METHOD(TensorFlow_SessionOptions, __destruct);
static PHP_METHOD(TensorFlow_SessionOptions, setTarget);

// argument info
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_session_options_setTarget, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()

// methods
static zend_function_entry tf_session_options_methods[] = {
    PHP_ME(TensorFlow_SessionOptions, __construct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_SessionOptions, __destruct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_SessionOptions, setTarget, arginfo_tf_session_options_setTarget, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

void define_tf_session_options_class()
{
    DEFINE_CLASS(SessionOptions, session_options, ce_TF_SessionOptions, oh_TF_SessionOptions)
}

CA_OBJECT_CREATE(session_options, t_tf_session_options, t_tf_session_options_object, oh_TF_SessionOptions)
CA_OBJECT_FREE(session_options, t_tf_session_options, t_tf_session_options_object)

// extern TF_SessionOptions* TF_NewSessionOptions();
static PHP_METHOD(TensorFlow_SessionOptions, __construct)
{
    t_tf_session_options_object* intern = TF_SESSION_OPTIONS_P_ZV(getThis());
    t_tf_session_options* node = intern->ptr;

    node->src = TF_NewSessionOptions();
}

// extern void TF_DeleteSessionOptions(TF_SessionOptions*);
static PHP_METHOD(TensorFlow_SessionOptions, __destruct)
{
    t_tf_session_options_object* intern = TF_SESSION_OPTIONS_P_ZV(getThis());
    t_tf_session_options* node = intern->ptr;

    TF_DeleteSessionOptions(node->src);
}

// extern void TF_SetTarget(TF_SessionOptions* options, const char* target);
static PHP_METHOD(TensorFlow_SessionOptions, setTarget)
{
    zend_string *target;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(target)
    ZEND_PARSE_PARAMETERS_END();

    // php_printf("target : %s\n", target->val);

    t_tf_session_options_object* intern = TF_SESSION_OPTIONS_P_ZV(getThis());
    t_tf_session_options* node = intern->ptr;

    TF_SetTarget(node->src, target->val);
}

// // Return a new options object.

// // Set the target in TF_SessionOptions.options.
// // target can be empty, a single entry, or a comma separated list of entries.
// // Each entry is in one of the following formats :
// // "local"
// // ip:port
// // host:port

// // Set the config in TF_SessionOptions.options.
// // config should be a serialized tensorflow.ConfigProto proto.
// // If config was not parsed successfully as a ConfigProto, record the
// // error information in *status.
// extern void TF_SetConfig(TF_SessionOptions* options, const void* proto,
//                          size_t proto_len, TF_Status* status);
