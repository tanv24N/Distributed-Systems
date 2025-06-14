#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//function to find modulo inverse of e under modulo phi
int mod_Inverse(int e, int phi) {
    for (int x = 1; x < phi; x++) {
        if ((e * x) % phi == 1)
            return x;
    }
    return -1;
}

//function to find Greatest Common Divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

//power function to perform modular exponentiation
long long int power(long long int base, int exp, int mod) {
    long long int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

//RSA Key Generation
void generateKeys(int *n, int *e, int *d) {
    //two prime numbers
    int p = 61, q = 53;  
    //public key
    *n = p * q;
    int phi = (p - 1) * (q - 1);

    //choose e such that 1 < e < phi and gcd(e, phi) = 1
    *e = 2;
    while (*e < phi) {
        if (gcd(*e, phi) == 1)
            break;
        else
            (*e)++;
    }

    //calculate d such that d * e % phi = 1
    *d = mod_Inverse(*e, phi);
    if (*d == -1) {
        printf("Modular inverse of e does not exist. Choose different primes.\n");
        exit(1);
    }
}

//Encryption function
int encrypt(int plaintext, int e, int n) {
    return power(plaintext, e, n);
}

//Decryption function
int decrypt(int ciphertext, int d, int n) {
    return power(ciphertext, d, n);
}

//main function
int main() {
    int n, e, d;
    generateKeys(&n, &e, &d);

    //printf("Public Key: (n = %d, e = %d)\n", n, e);
    //printf("Private Key: (n = %d, d = %d)\n", n, d);

    // Input plaintext
    char plaintext[256];
    printf("Enter plaintext:- ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;

    int length = strlen(plaintext);
    int encrypted[length];
    int decrypted[length];

    printf("Encrypted Ciphertext:- ");
    for (int i = 0; i < length; i++) {
        encrypted[i] = encrypt((int)plaintext[i], e, n);
        printf("%d ", encrypted[i]);
    }
    printf("\n");

    printf("Decrypted Plaintext:- ");
    for (int i = 0; i < length; i++) {
        decrypted[i] = decrypt(encrypted[i], d, n);
        printf("%c", (char)decrypted[i]);
    }
    printf("\n");

    return 0;
}
