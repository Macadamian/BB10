MoshPitHero
===========

This is a demo application to showcase the art of the possible on the Blackberry 10 Platform.
It is made using the Cocos2dx 2D game engine, Box2D physics engine and the Cascades Framework.

The premise is that of a music festival where you walk in and based on your geofence, twitter feed, 
contact information, calendar etc. the app will show you relevant information in a fun and immersive
user interface. For the purposes of the demo most of the data collection and processing is not done
and instead placeholder data is used. Even so, there is code to interface with many of the built in
apps and features offered by the Blackberry 10 platform.


Features Implemented:
- Falling objects are affected by the accelerometer and have physical properties. You can interact 
  with them via multi-touch.
- Long press on twitter feed to have deeper interction via a cascades info bubble. 
- Throw falling objects (friend bubbles, stars, stage/location info, etc.) on stage to see cascades
  info bubble.
- All cascades info bubbles have context menus on long press based on their data.
- Only some of the context menu action items are linked to their real actions. Code exists for most
  of them, they just need to be linked.
- You can discard objects you dont like by flicking them to either side after throwing them on stage.
- Long press on an object to see other related objects that start orbiting.
- Throw objects with related objects onto stage to spawn more falling objects.
- Swipe background to either side to view other stages.
- Red stage has the Vivek demo closer guy cameo coupon.
- Animated map view to view the location of other friends in the event.



Building this Sample
--------------------

Import all the projects into your workspace then build and run the moshpithero project.