# Creature Formations in game command

## Description

This modules allows you to add creature_formations entries from in game; simplifying the process of fixing raids and
dungeons that have incorrectly linked mob pulls by easily adding links for their GUIDS.

## How to use ingame

Arguments with * are required, rest are optional.

.pack create leaderGUID* memberGUID* groupAI dist angle
.pack disband leaderGUID*

e.g.  

.pack create 114764 2023271  
.pack create 114764 2023271 515  
.pack create 114764 2023271 515 2  
.pack create 114764 2023271 515 2 270  


## Installation

```
1) Simply `git clone` the module under the `modules` directory of your AzerothCore source or copy paste it manually.
2) Re-run cmake and launch a clean build of AzerothCore.
```


## Credits

* [mdjong1](https://github.com/mdjong1)
* AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
