# Avengers' Quantum Suit Upgrade

## Project Overview
The **Avengers' Quantum Suit Upgrade** is a battle simulation system designed using Object-Oriented Programming (OOP) principles. This project involves managing **Quantum Nanotech Suits (QNS)** that dynamically adapt and upgrade based on battlefield conditions.

## Objective
- Design a **Quantum Suit Management System** for Avengers.
- Implement **polymorphism, operator overloading, and function overloading** to handle real-time suit upgrades, attacks, and defenses.
- Simulate a battle between Avengers and their enemies.

## Features
### 1. Quantum Nanotech Suit (QNS)
- Each suit has the following attributes:
  - **Power Level (P)** - Attack strength.
  - **Durability (D)** - Defensive strength.
  - **Energy Storage (E)** - Stores absorbed energy from enemy attacks.
  - **Heat Level (H)** - Increases with overuse and can cause shutdown.

- **Operator Overloading:**
  - `+` : Upgrade suit using stored energy.
  - `-` : Simulate attack damage.
  - `*` : Activate **Power Boost** mode.
  - `/` : Reduce heat by transferring energy to durability.

- **Function Overloading:**
  - Boost power with a factor.
  - Boost power using energy from another suit.

- **Comparison Overloading:**
  - `==` : Compare two suits based on power and durability.
  - `<` : Compare the effectiveness of suits.

### 2. Avengers
- Each Avenger has:
  - **Name**
  - **Quantum Suit**
  - **Attack Strength**

- **Actions:**
  - Attack an enemy.
  - Upgrade their suit.
  - Repair their suit.

### 3. Battle System
- Handles **battle simulation** between Avengers and enemies.
- Maintains a **battle log** to track actions.
- Determines **battle outcome** based on total power and durability.

## System Constraints
- Maximum **Power Level**: **5000**
- Suit **overheats** if Heat Level exceeds **500**.
- If **Durability = 0**, the suit is destroyed.
- Suit assignment follows a **first-come, first-served** basis.

## Input Format
1. Initialization:
   ```
   k n m
   ```
   - `k` = Number of Quantum Suits.
   - `n` = Number of Avengers.
   - `m` = Number of Enemies.

2. Suit Details:
   ```
   P D E H
   ```
   - Power Level, Durability, Energy Storage, Heat Level.

3. Avenger & Enemy Details:
   ```
   Name AttackStrength
   ```
   - Each Avenger/Enemy is assigned a suit.

## Commands
- **BattleBegin**: Starts the battle.
- **Attack A B**: `A` attacks `B`.
- **Repair A x**: `A` repairs `x` durability.
- **BoostPowerByFactor A y**: `A` boosts power by factor `y`.
- **BoostPower A P D E H**: `A` transfers energy from another suit.
- **Upgrade A**: `A` upgrades suit if extra suits are available.
- **AvengerStatus A**: Prints the suit status of `A`.
- **PrintBattleLog**: Displays battle history.
- **BattleStatus**: Displays the current winner.
- **End**: Ends the simulation.

## Sample Input/Output
**Input:**
```
3 2 2
1000 500 300 0
1200 700 200 10
1500 800 400 20
IronMan 100
Thor 150
Loki 120
Ultron 180
BattleBegin
Attack IronMan Loki
Attack Thor Loki
Repair IronMan 50
BoostPowerByFactor Thor 2
Upgrade IronMan
AvengerStatus IronMan
AvengerStatus Thor
PrintBattleLog
BattleStatus
End
```

**Output:**
```
Ultron is out of fight
IronMan 1000 550 300 0
Thor 1224 700 210 12
IronMan attacks Loki
Thor attacks Loki
IronMan repaired
Thor boosted
IronMan upgrade Fail
heroes are winning
```