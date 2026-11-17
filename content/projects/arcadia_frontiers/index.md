# Arcadia Frontiers

[< Back Home](/)

![Arcadia Frontiers image](/images/arcadia_frontiers_1.png)

## About

Arcadia Frontiers is a multiplayer top-down action fantasy extraction game. I made it to mix many of the genres in games I am a huge fan of but have not seen put together in one game yet.

## Architecture

Arcadia Frontiers utilizes a hybrid client server architecture with client-side prediction and server side reconciliation. The client-side prediction is utilized to eliminate the delay between player input and what is rendered in the game state. The client can assume the inputs that are sent to the server will be executed successfully. And under this assumption, the client can predict the game state after inputs are processed, and most of the time this will be correct. The correct game state is sent back by the server which has ultimate authority over the game state, but the prediction is usually correct. Overall, this improves responsiveness and smoothness client side while still maintaining server authority to maintain game security.

![Playing Together](/images/arcadia_frontiers_2.png)

## Multiplayer

Multiplayer was a feature I wanted since I first had Arcadia Frontiers as a brain child. The original project started out as a single player top-down action fantasy extraction game because I did not think that multiplayer was feasible. But after getting pretty far with the single player version, I decided to transfer those core elements to a multiplayer framework before I was in too deep optimizing for a single player architecture.

![Boss Fight](/images/arcadia_frontiers_3.png)

## Niche

As far as I am aware, Arcadia Frontiers is the only game that is in the extremely niche genre of multiplayer top-down action fantasy extraction. While there are top-down extraction games and plenty of multiplayer fantasy games that may also be top-down. Nothing that is currently out there is multiplayer, top-down, action, fantasy, and extraction all in one. It just has not been done yet.

## 