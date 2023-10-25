# Zombie Arena

### Description

This game is a modification of the Zombie Arena game made by John Horton in his book "Beginning C++ Game Programming - Second Edition." In this modification, various
pickups and obstacles have been added, and the zombies behave differently.

### Changes made

- Added multishot pickup that allows the user to shoot more than one bullet at a time (will shoot in multiple directions).
- Added shield pickup that protects the player, the player will only take damage when the shield is broken.
- Added wall obstacle that the players and zombies cannot pass through.
- Added a lava obstacle that damages the player and zombies over time.
- Changed Chaser Zombie behavior. When hit, they flee briefly and then resume chasing the player.
- Changed Bloater Zombie behavior. When the bloater gets down to 1 health they stop and explode.
- Changed Crawler Zombie behavior. When hit, the crawler's speed will increase.
