# BattleTank
Section 4 of the course: an open-world battle tank game

## Game design document (GDD)

### Concept

It's a survival "enemy-wave" kind of game, structured in progressively harder levels where the player drives a 
war tank that needs to survive other tank enemies for a given period of time. At the beginning of each level, the player 
chooses the equipment, that can be purchased thanks to a local currency system based on performance (mainly based on how many enemies were 
defeated and the level difficulty). Levels become harder as more and more powerful enemies are spawned, which is compensated by the player gaining a better equipment 
and aids spawning across the map. 

The equipment is of three types:
1. Weapons, characterized by
   - a name
   - a power value
   - a precision value (the higher the less becomes the error with respect to the aim)
   - ammo type (armor-piercing, ...)

2. Armor, characterized by
   - a name
   - a resistance value
  
3. Engine, characterized by
   - a belt speed (vehicle speed)
   - a turret speed (mouse sensitivity)

The aid type include:
1. Additional ammo;
2. Special ammo;
3. Temporary armor;
4. Medikits;
5. ...

### Rules

- Movement is planar (no jumping);
- A level is won if the player survives the horde for the level's duration;
- Total number of levels could be indefinite... TBD

### Requirements

1. Menu:
   - For now, just START and QUIT

2. SFX:
    - Explosion effect on tank;
    - Explosion effect on terrain;
    - Intensity of smoke on tanks to measure health;

3. HUD: 
    - Health and ammo
    - Coins
    - Minimap showing enemies and aids when spawned
    - Time to the end of the level

4. Static meshes:
    - Tank(s)
    - Trees
    - Rocks

5. Landscape:
    - Possibly randomly placed hills and obstacles?
    

