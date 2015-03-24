package eu.luminis.devcon.rest;

import javax.ws.rs.POST;
import javax.ws.rs.Path;

import eu.luminis.devcon.RocketLauncher;

@Path("rocket_launcher")
public class RocketLauncherRest {
	private RocketLauncher rocketLauncher;
	
	@POST
	@Path("stop")
	public void stop() {
		System.out.println("STOP!!");
		rocketLauncher.stop();
	}
	
	@POST
	@Path("up")
	public void up() {
		System.out.println("UP!!");
		rocketLauncher.up();
	}
	
	@POST
	@Path("down")
	public void down() {
		System.out.println("DOWN!!");
		rocketLauncher.down();
	}
	
	@POST
	@Path("left")
	public void left() {
		System.out.println("LEFT!!");
		rocketLauncher.left();
	}
	
	@POST
	@Path("right")
	public void right() {
		System.out.println("RIGHT!!");
		rocketLauncher.right();
	}
	
	@POST
	@Path("fire")
	public void fire() {
		System.out.println("FIRE!!");
		rocketLauncher.fire();
	}
	
	@POST
	@Path("reset")
	public void reset() {
		System.out.println("RESET!!");
		rocketLauncher.reset();
	}
}
