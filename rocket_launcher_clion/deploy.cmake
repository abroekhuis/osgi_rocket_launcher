deploy( "rocket_launcher" BUNDLES
		${CELIX_BUNDLES_DIR}/shell.zip
		${CELIX_BUNDLES_DIR}/shell_tui.zip
		${CELIX_BUNDLES_DIR}/log_service.zip
		${CELIX_BUNDLES_DIR}/topology_manager.zip
		${CELIX_BUNDLES_DIR}/remote_service_admin_http.zip
		${CELIX_BUNDLES_DIR}/discovery_configured.zip
		eu.luminis.devcon.rocket_launcher_component
		eu.luminis.devcon.rocket_launcher_console
	ENDPOINTS
		eu.luminis.devcon.RocketLauncher_endpoint
	PROPERTIES
		RSA_PORT=8001
		DISCOVERY_CFG_POLL_ENDPOINTS=http://localhost:9000/org.amdatu.remote.discovery.configured
		DISCOVERY_CFG_SERVER_PORT=9999
)
