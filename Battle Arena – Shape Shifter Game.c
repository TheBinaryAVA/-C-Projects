#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==============================
// 1️⃣ Character Union Definition
// ==============================

typedef union {
    struct {
        int strength;
    } warrior;

    struct {
        int mana;
    } mage;

    struct {
        int accuracy;
    } archer;

} CharacterStats;

// ==============================
// 2️⃣ Bit-field for status
// ==============================

union Status {
    unsigned int value;
    struct {
        unsigned int poisoned:1;
        unsigned int stunned:1;
        unsigned int shielded:1;
    } effects;
};

// ==============================
// 3️⃣ Tagged Character Structure
// ==============================

typedef struct {
    int type;   // 1=Warrior, 2=Mage, 3=Archer
    int health;
    CharacterStats stats;
    union Status status;
} Character;


// ==============================
// Function Prototypes
// ==============================

void createCharacter(Character *c);
void attack(Character *attacker, Character *defender);
void showCharacter(Character c);
void applyRandomStatus(Character *c);


// ==============================
// MAIN
// ==============================

int main() {

    Character player, enemy;

    printf("=== BATTLE ARENA ===\n");

    printf("\nCreate your character:\n");
    createCharacter(&player);

    printf("\nCreating enemy...\n");
    enemy.type = rand() % 3 + 1;
    enemy.health = 100;
    enemy.status.value = 0;

    if(enemy.type == 1)
        enemy.stats.warrior.strength = 20;
    else if(enemy.type == 2)
        enemy.stats.mage.mana = 30;
    else
        enemy.stats.archer.accuracy = 25;

    printf("\n--- BATTLE STARTS ---\n");

    showCharacter(player);
    showCharacter(enemy);

    attack(&player, &enemy);

    printf("\nAfter attack:\n");
    showCharacter(enemy);

    return 0;
}


// ==============================
// Create Character
// ==============================

void createCharacter(Character *c) {

    printf("Choose type (1=Warrior, 2=Mage, 3=Archer): ");
    scanf("%d", &c->type);

    c->health = 100;
    c->status.value = 0;

    switch(c->type) {
        case 1:
            printf("Enter strength: ");
            scanf("%d", &c->stats.warrior.strength);
            break;
        case 2:
            printf("Enter mana: ");
            scanf("%d", &c->stats.mage.mana);
            break;
        case 3:
            printf("Enter accuracy: ");
            scanf("%d", &c->stats.archer.accuracy);
            break;
        default:
            printf("Invalid type\n");
    }
}


// ==============================
// Attack Function (Pointer to Union)
// ==============================

void attack(Character *attacker, Character *defender) {

    int damage = 0;

    switch(attacker->type) {
        case 1:
            damage = attacker->stats.warrior.strength;
            break;
        case 2:
            damage = attacker->stats.mage.mana;
            break;
        case 3:
            damage = attacker->stats.archer.accuracy;
            break;
    }

    defender->health -= damage;

    printf("\nAttack deals %d damage!\n", damage);

    applyRandomStatus(defender);
}


// ==============================
// Random Status Effects (Bit-field)
// ==============================

void applyRandomStatus(Character *c) {

    int effect = rand() % 3;

    if(effect == 0)
        c->status.effects.poisoned = 1;
    else if(effect == 1)
        c->status.effects.stunned = 1;
    else
        c->status.effects.shielded = 1;

    printf("Status Applied!\n");
}


// ==============================
// Display Character Info
// ==============================

void showCharacter(Character c) {

    printf("\nHealth: %d\n", c.health);

    switch(c.type) {
        case 1:
            printf("Type: Warrior | Strength: %d\n",
                   c.stats.warrior.strength);
            break;
        case 2:
            printf("Type: Mage | Mana: %d\n",
                   c.stats.mage.mana);
            break;
        case 3:
            printf("Type: Archer | Accuracy: %d\n",
                   c.stats.archer.accuracy);
            break;
    }

    if(c.status.effects.poisoned)
        printf("Status: Poisoned\n");
    if(c.status.effects.stunned)
        printf("Status: Stunned\n");
    if(c.status.effects.shielded)
        printf("Status: Shielded\n");
}
