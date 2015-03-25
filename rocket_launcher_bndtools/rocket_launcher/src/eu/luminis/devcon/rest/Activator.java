package eu.luminis.devcon.rest;

import org.apache.felix.dm.DependencyActivatorBase;
import org.apache.felix.dm.DependencyManager;
import org.osgi.framework.BundleContext;

import eu.luminis.devcon.RocketLauncher;

public class Activator extends DependencyActivatorBase {

	@Override
	public void init(BundleContext arg0, DependencyManager manager)
			throws Exception {
		manager.add(createComponent()
				.setInterface(Object.class.getName(), null)
				.setImplementation(RocketLauncherRest.class)
				.setCallbacks(null, null, null, null)
				.add(createServiceDependency().setService(RocketLauncher.class).setRequired(true))
				);
		
	}
	
	@Override
	public void destroy(BundleContext arg0, DependencyManager arg1)
			throws Exception {
		// TODO Auto-generated method stub
		
	}

}
