SET(BUNDLE_SYMBOLICNAME "eu.luminis.devcon.RocketLauncher_endpoint")
SET(BUNDLE_VERSION "0.0.1")

include_directories("${CELIX_INCLUDE_DIR}")
include_directories("${CELIX_INCLUDE_DIR}/log_service")
include_directories("${JANSSON_INCLUDE_DIRS}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/private/include")
include_directories("../rocket_launcher/public/include")
include_directories("${CELIX_INCLUDE_DIR}/dependency_manager_2")

bundle(
    SOURCES 
		private/src/rocket_launcher_endpoint.c
		private/src/dependency_activator.c
		${CELIX_BUNDLES_DIR}/../log_service/log_helper.c
	LINK_LIBRARIES
        -Wl,--whole-archive /opt/local/lib/libdependency_manager2.a -Wl,--no-whole-archive ${CELIX_FRAMEWORK_LIBRARY} ${CELIX_UTILS_LIBRARY} ${JANSSON_LIBRARIES}
)
