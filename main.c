#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @brief nacitaj   Funkcia nacitava vstup a uklada ho do dvoch poli.
 * @param string    Pole znakov typu uint8_t, do ktoreho sa uklada zadany retazec po prvy biely znak
 * @param formula   Pole znakov typu char, do ktoreho sa uklada formula, konci pri prvom vyskyte '\n'
 * @param pocet     Pointer na premennu, ktora si pamata nacitany pocet znakov zadaneho retazca na pretransformovaie
 *
 * Funkcia si spociatku nacitava retazec na pretransformovanie. Ak dostane na vstup hned na zaciatku alebo po zadani
 * retazca na pretransformovanie znak '\n', skonci. V opacnom pripade nacita retazec dlzky max. 50 pozostavajuci
 * z operandov a operatorov, t.j. formula.
 */

void nacitaj(uint8_t *string, char *formula, uint8_t *pocet) {
    uint8_t znak = getchar();
    if (znak == '\n')
        return;
    while (((isspace(znak)) == 0) && ((*pocet) != 50)) {
        string[(*pocet)] = znak;
        (*pocet)++;
        znak = getchar();
    } 
    if (znak == '\n')
        return;

    fgets(formula, 51, stdin);

}

/**
 * @brief           Seria funkcii, ktora vykonava jednotlive operacie.
 * @param string    Retazec na pretransformovanie
 * @param operand   Operand, s ktorym sa bude pracovat
 * @param pocet     Pocet znakov v retazci, pocita sa vo funkcii nacitaj()
 * @param boolean   Nadobuda hodnotu 1 v pripade, ak na vstup dostanem operand 'i', inak 0
 *
 * Kazda z funkcii (okrem bitovej negace) pracuje obdobnym sposobom. Najprv testuje hodnotu @a boolean,
 * podla toho vykona cyklus, kde je operandom hodnota riadiacej premennej (boolean == 1),
 * v opacnom pripade pracuje s @a operand.
 *
 * Funkcia bitNegace() na vstup dostane iba @a string a @a pocet , kedze ziadne operandy nepotrebuje.
 */

void soucet(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] += i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] += operand;
        }
    }
}

void rozdil(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] -= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] -= operand;
        }
    }
}

void nasobeni(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] *= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] *= operand;
        }
    }
}

void podil(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] /= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] /= operand;
        }
    }
}

void zbytek(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] %= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] %= operand;
        }
    }
}

void bitSoucin(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] &= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] &= operand;
        }
    }
}

void bitSoucet(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] |= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] |= operand;
        }
    }
}

void exklBitSoucet(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] ^= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] ^= operand;
        }
    }
}

void posunDoleva(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] <<= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] <<= operand;
        }
    }
}

void posunDoprava(uint8_t *string, uint8_t operand, uint8_t pocet, uint8_t boolean) {
    if (boolean == 1) {
        for (uint8_t i = 0; i < pocet; i++)
            string[i] >>= i;
    } else {
        for (uint8_t i = 0; i < pocet; i++) {
            string[i] >>= operand;
        }
    }
}

void bitNegace(uint8_t *string,  uint8_t pocet) {
    for (uint8_t i = 0; i < pocet; i++) {
        string[i] = ~(string[i]);
    }
}

/**
 * @brief transformace  Funkcia parsuje formulu a zaroven postupne vykonava jednotlive operacie.
 * @param string        Retazec na pretransformovanie
 * @param formula       Formula na rozparsovanie
 * @param pocet         Pocet znakov v retazci
 *
 * Funkcia si na zaciatku vytvori dve lokalne premenne, ktore nastavi na nulu. Premenna boolean sa zvysi v pripade,
 * ak na vstup dostanem operand 'i', v opacnom pripade zostava nezmenena. Do premennej token sa ulozi ukazatel na prvy
 * retazec konciaci znakom medzery alebo znakom '\n'. Ukazatel operation sa inicializuje na rovnaku hodnotu, ako je token.
 *
 * Nasleduje cyklus, ktory sa opakuje az do momentu, kedy ukazatel token ukazuje na NULL. V pripade, ak je operator
 * znak '~', vykona sa funkcia bitNegace(), v opacnom pripade dalej rozparsujeme formulu. Ak je operand znak 'i', boolean
 * sa zvysi. Do premennej operand sa vlozi pretransformane cislo zo vstupu.
 *
 * Dalej pokracuje funkciu switchom, kde vykona taku operaciu, ktora je ulozena na adrese, kam ukazuje ukazatel operation.
 *
 * Po vykonani prislusnej operacie sa formula dalej rozparsuje, do premennej operation sa ulozi hodnota tokenu a
 * boolean sa nastavi na nulu. Nasleduje dalsia iteracia cyklu, ak sa token nerovna NULL.
 */

void transformace(uint8_t *string, char *formula, uint8_t pocet) {
    uint8_t boolean = 0;
    uint8_t operand = 0;
    char *token = strtok(formula, " \n");
    char *operation = token;
    while (token != NULL) {
        if (!(strcmp(token,"~"))) {
           bitNegace(string, pocet);
        } else {
            token = strtok(NULL, " \n");
            if (!(strcmp(token,"i"))) {
                boolean++;
            }
            operand = (uint8_t) atoi(token);
            switch(*operation) {
            case '+':
                soucet(string, operand, pocet, boolean);
                break;
            case '-':
                rozdil(string, operand, pocet, boolean);
                break;
            case '*':
                nasobeni(string, operand, pocet, boolean);
                break;
            case '/':
                podil(string, operand, pocet, boolean);
                break;
            case '%':
                zbytek(string, operand, pocet, boolean);
                break;
            case '&':
                bitSoucin(string, operand, pocet, boolean);
                break;
            case '|':
                bitSoucet(string, operand, pocet, boolean);
                break;
            case '^':
                exklBitSoucet(string, operand, pocet, boolean);
                break;
            case '<':
                posunDoleva(string, operand, pocet, boolean);
                break;
            case '>':
                posunDoprava(string, operand, pocet, boolean);
                break;
            }
        }
        token = strtok(NULL, " \n");
        operation = token;
        boolean = 0;
    }
}

/**
 * Vo funkcii main() sa spociatku inicializuju premenne.
 * Pocet sa nastavi najprv na nulu, do funkcie nacitaj() predavame jeho adresu, aby sme ju mohli zmenit a dalej
 * s nou pracovat. Inicializuju sa polia string[] a formula[], vykonaju sa obe vyznamne funkcie nacitaj() a transformace().
 *
 * V pripade, ak na vstup nedostanem nijaky dalsi parameter okrem cesty k suboru, vypisem retazec v sestnastkovej sustave.
 * V opacnom pripade porovnavam zadany retazec s retazcom "-i" alebo "-s" a vypisem ho v desiatkovej sustave
 * bez znamienka alebo ako retazec znakov. Ak dostanem na vstup iny parameter, vypisem retazec iba v sestnastkovej
 * sustave.
 */

int main(int argc, char **argv)
{
    uint8_t pocet = 0;
    uint8_t string[51] = {0};
    char formula[52] = "";
    nacitaj(string, formula, &pocet);
    transformace(string, formula, pocet);

    if (argc == 1) {
        for (int i = 0; i < pocet; i++) {
            printf("%02X", string[i]);
        }
    } else {
        if (!(strcmp(argv[1], "-s"))) {
            for (int i = 0; i < pocet; i++) {
                putchar(string[i]);
            }
        } else if (!(strcmp(argv[1], "-i"))) {
            for (int i = 0; i < pocet; i++) {
                printf("%u", string[i]);
            }
        } else {
            for (int i = 0; i < pocet; i++) {
                printf("%02X", string[i]);
            }
        }
    }
    printf("\n");
    return 0;
}

