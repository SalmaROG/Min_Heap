#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

void afficherVecteur(const vector<int>& vecteur) 
{
    for (int val : vecteur) 
    {
        cout << val << " ";
    }
    cout << endl;
}

void remplirVecteur(vector<int>& vecteur, int taille, int minVal, int maxVal) 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);

    for (int i = 0; i < taille; ++i) 
    {
        vecteur.push_back(distrib(gen));
    }
}

void insererDansTasMin(vector<int>& tasMin, int valeur) 
{
    tasMin.push_back(valeur);
    int index = tasMin.size() - 1;

    while (index > 0) 
    {
        int indexParent = (index - 1) / 2;
        if (tasMin[index] < tasMin[indexParent])
        {
            swap(tasMin[index], tasMin[indexParent]);
            index = indexParent;
        }
        else
        {
            break;
        }
    }
}

void reorganiserTasMin(vector<int>& tasMin, int index)
{
    int filsGauche = 2 * index + 1;
    int filsDroit = 2 * index + 2;
    int plusPetit = index;

    if (filsGauche < tasMin.size() && tasMin[filsGauche] < tasMin[plusPetit]) 
    {
        plusPetit = filsGauche;
    }
    if (filsDroit < tasMin.size() && tasMin[filsDroit] < tasMin[plusPetit])
    {
        plusPetit = filsDroit;
    }

    if (plusPetit != index) 
    {
        swap(tasMin[index], tasMin[plusPetit]);
        reorganiserTasMin(tasMin, plusPetit);
    }
}

void supprimerRacine(vector<int>& tasMin) 
{
    if (tasMin.empty()) return;

    tasMin[0] = tasMin.back();
    tasMin.pop_back();
    reorganiserTasMin(tasMin, 0);
}

void trierTasMin(vector<int>& tasMin) 
{
    vector<int> resultat;

    while (!tasMin.empty()) 
    {
        resultat.push_back(tasMin[0]);
        supprimerRacine(tasMin);
    }

    cout << "Tas Min apres le tri : " << endl;
    afficherVecteur(resultat);
}

bool rechercherDansTas(const vector<int>& tasMin, int valeur)
{
    for (int val : tasMin) 
    {
        if (val == valeur)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    vector<int> vecteurOriginal;
    vector<int> tasMin;

    int taille = 20;  
    int minVal = 1, maxVal = 100;

    // Remplir le vecteur avec des valeurs aléatoires
    remplirVecteur(vecteurOriginal, taille, minVal, maxVal);

    cout << "Vecteur original avec des valeurs aleatoires : " << endl;
    afficherVecteur(vecteurOriginal);

    // Insérer les valeurs dans le tas min
    for (int valeur : vecteurOriginal) 
    {
        insererDansTasMin(tasMin, valeur);
    }

    cout << "\nTas Min avant le tri : " << endl;
    afficherVecteur(tasMin);
    cout << endl;

    // Trier le tas min
    trierTasMin(tasMin);

    
    // Recherche d'une valeur dans le tas
    int valeur;
    cout << "\nEntrez une valeur a rechercher dans le tas : ";
    cin >> valeur;

    if (rechercherDansTas(vecteurOriginal, valeur)) {
        cout << "Valeur " << valeur << " trouvee dans le tas." << endl;
    }
    else {
        cout << "Valeur " << valeur << " non trouvee dans le tas." << endl;
    }

    // Temps d'exécution
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nTemps d'execution : " << duration.count() << " secondes." << endl;

    return 0;
}
