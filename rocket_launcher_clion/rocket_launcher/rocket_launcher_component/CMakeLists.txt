

SET(
	BUNDLE_NAME 
"rocket_launcher_component"
)

SET(
	BUNDLE_SYMBOLICNAME 
"eu.luminis.devcon.rocket_launcher_component"
)

SET(BUNDLE_VERSION "0.0.1")

include_directories(
	"private/include"
	"public/include"
	"${PROJECT_SOURCE_DIR}/rocket_launcher/rocket_launcher/public/include"
	${CELIX_INCLUDE_DIR}/dependency_manager_2
)
include_directories("${CELIX_INCLUDE_DIR}/remote_service_admin")

bundle(
	SOURCES
		private/src/dependency_activator
		private/src/rocket_launcher_component

		private/include/rocket_launcher_component
	LINK_LIBRARIES
		${CELIX_FRAMEWORK_LIBRARY}
		${CELIX_UTILS_LIBRARY}
		-Wl,-all_load /Users/abroekhuis/Development/Celix/usr/local/lib/libdependency_manager2.a
)

#IF(APPLE)
#target_link_libraries(${BUNDLE_LIB} ${CELIX_FRAMEWORK_LIBRARY} ${CELIX_UTILS_LIBRARY} -Wl,-all_load /Users/abroekhuis/Development/Celix/usr/local/lib/libdependency_manager2.a)
#else()
#target_link_libraries(${BUNDLE_LIB} -Wl,--whole-archive dependency_manager2 -Wl,--no-whole-archive ${CELIX_FRAMEWORK_LIBRARY} ${CELIX_UTILS_LIBRARY})
#ENDIF()
