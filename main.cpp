/*
 * Kolkata Metro - Dijkstra's Algorithm
 *
 * NODE MAP (57 stations, nodes 0-56):
 *
 * BLUE LINE (Line 1) | Dakshineswar to Kavi Subhash
 *  0  Dakshineswar
 *  1  Baranagar
 *  2  Noapara[interchange: Yellow Line node 50]
 *  3  Dum_Dum
 *  4  Belgachhia
 *  5  Shyambazar
 *  6  Shobhabazar_Sutanuti
 *  7  Girish_Park
 *  8  MG_Road
 *  9  Central
 * 10  Chandni_Chowk
 * 11  Esplanade[interchange: Green Line node 31]
 * 12  Park_Street
 * 13  Maidan
 * 14  Rabindra_Sadan
 * 15  Netaji_Bhavan
 * 16  Jatin_Das_Park
 * 17  Kalighat
 * 18  Rabindra_Sarobar
 * 19  Mahanayak_Uttam_Kumar
 * 20  Netaji
 * 21  Masterda_Surya_Sen
 * 22  Gitanjali
 * 23  Kavi_Nazrul
 * 24  Shahid_Khudiram
 * 25  Kavi_Subhash[interchange: Orange Line node 38]
 *GREEN LINE (Line 2) | Howrah Maidan to Salt Lake Sector-V
 * 26  Howrah_Maidan[interchange: Orange Line node 47]
 * 27  Howrah
 * 28  Mahakaran
 * 29  Esplanade_GL [same physical station as node 11, edge weight 0 treated as 1]
 * 30  Sealdah[interchange: Orange Line node 45]
 * 31  Phoolbagan[interchange: Orange Line node 44]
 * 32  SV_Marg
 * 33  Karunamoyee
 * 34  Central_Park
 * 35  City_Centre
 * 36  Bengal_Chemical
 * 37  Salt_Lake_Sector_V
 * PURPLE LINE (Line 3) | Joka to Majerhat
 * 38  Joka
 * 39  Thakurpukur
 * 40  Sakherbazar
 * 41  Behala_Chowrasta
 * 42  Behala_Bazar
 * 43  Taratala
 * 44  Majerhat
 * ORANGE LINE (Line 6)[Kavi Subhash to Hemanta Mukhopadhyay ]
 * 45  Kavi_Subhash_OL[interchange with Blue Line node 25]
 * 46  Satyajit_Ray
 * 47  Kazi_Nazrul_Islam
 * 48  Hemanta_Mukhopadhyay
 * 49  Beleghata
 * 50  Phoolbagan_OL [interchange with Green Line node 31]
 * 51  Sealdah_OL[interchange with Green Line node 30]
 * 52  Esplanade_OL [interchange with Blue Line node 11 & Green Line node 29]
 * 53  Howrah_Maidan_OL [interchange with Green Line node 26]
 * YELLOW LINE (Line 4) | Noapara to Jai Hind
 * 54  Noapara_YL [interchange with Blue Line node 2]
 * 55  Bagjola
 * 56  Jai_Hind
 * INTERCHANGE EDGES (transfer between lines, weight = 1):
 *   Blue  node 11  <-> Green  node 29  (Esplanade)
 *   Blue  node 25  <-> Orange node 45  (Kavi Subhash)
 *   Green node 26  <-> Orange node 53  (Howrah Maidan)
 *   Green node 30  <-> Orange node 51  (Sealdah)
 *   Green node 31  <-> Orange node 50  (Phoolbagan)
 *   Blue  node 11  <-> Orange node 52  (Esplanade)
 *   Green node 29  <-> Orange node 52  (Esplanade)
 *   Blue  node  2  <-> Yellow node 54  (Noapara)
 */

#include<bits/stdc++.h>
#include<string>
#include<climits>
using namespace std;

#define N 57

int mindistance(int distance[], bool stat[])
{
    int minimum = INT_MAX, ind = 0;
    for (int k = 0; k < N; k++)
    {
        if (stat[k] == false && distance[k] <= minimum)
        {
            minimum = distance[k];
            ind = k;
        }
    }
    return ind;
}

void dijkstra(int graph[N][N], int source, string stations[N])
{
    int distance[N];
    bool stat[N];
    for (int k = 0; k < N; k++)
    {
        distance[k] = INT_MAX;
        stat[k] = false;
    }
    distance[source] = 0;
    for (int k = 0; k < N; k++)
    {
        int m = mindistance(distance, stat);
        stat[m] = true;
        for (int j = 0; j < N; j++)
        {
            if (!stat[j] && graph[m][j] && distance[m] != INT_MAX && distance[m] + graph[m][j] < distance[j])
                distance[j] = distance[m] + graph[m][j];
        }
    }
    cout << "\nMinimum Stations (hops) from " << stations[source] << " to every station:\n" << endl;
    for (int k = 0; k < N; k++)
    {
        if (distance[k] == INT_MAX)
            cout << stations[source] << "  ->  " << stations[k] << "  :  UNREACHABLE" << endl;
        else
            cout << stations[source] << "  ->  " << stations[k] << "  :  " << distance[k] << endl;
    }
}

int main()
{ // 57x57 adjacency matrix, all zeros initially
    int graph[N][N] = {};
    // Helper lambda to add undirected edge
    auto addEdge = [&](int u, int v) {
        graph[u][v] = 1;
        graph[v][u] = 1;
    };
    // BLUE LINE (nodes 0-25) ─
    addEdge(0, 1);   // Dakshineswar - Baranagar
    addEdge(1, 2);   // Baranagar - Noapara
    addEdge(2, 3);   // Noapara - Dum_Dum
    addEdge(3, 4);   // Dum_Dum - Belgachhia
    addEdge(4, 5);   // Belgachhia - Shyambazar
    addEdge(5, 6);   // Shyambazar - Shobhabazar_Sutanuti
    addEdge(6, 7);   // Shobhabazar_Sutanuti - Girish_Park
    addEdge(7, 8);   // Girish_Park - MG_Road
    addEdge(8, 9);   // MG_Road - Central
    addEdge(9, 10);  // Central - Chandni_Chowk
    addEdge(10, 11); // Chandni_Chowk - Esplanade
    addEdge(11, 12); // Esplanade - Park_Street
    addEdge(12, 13); // Park_Street - Maidan
    addEdge(13, 14); // Maidan - Rabindra_Sadan
    addEdge(14, 15); // Rabindra_Sadan - Netaji_Bhavan
    addEdge(15, 16); // Netaji_Bhavan - Jatin_Das_Park
    addEdge(16, 17); // Jatin_Das_Park - Kalighat
    addEdge(17, 18); // Kalighat - Rabindra_Sarobar
    addEdge(18, 19); // Rabindra_Sarobar - Mahanayak_Uttam_Kumar
    addEdge(19, 20); // Mahanayak_Uttam_Kumar - Netaji
    addEdge(20, 21); // Netaji - Masterda_Surya_Sen
    addEdge(21, 22); // Masterda_Surya_Sen - Gitanjali
    addEdge(22, 23); // Gitanjali - Kavi_Nazrul
    addEdge(23, 24); // Kavi_Nazrul - Shahid_Khudiram
    addEdge(24, 25); // Shahid_Khudiram - Kavi_Subhash
    // GREEN LINE (nodes 26-37) 
    addEdge(26, 27); // Howrah_Maidan - Howrah
    addEdge(27, 28); // Howrah - Mahakaran
    addEdge(28, 29); // Mahakaran - Esplanade_GL
    addEdge(29, 30); // Esplanade_GL - Sealdah
    addEdge(30, 31); // Sealdah - Phoolbagan
    addEdge(31, 32); // Phoolbagan - SV_Marg
    addEdge(32, 33); // SV_Marg - Karunamoyee
    addEdge(33, 34); // Karunamoyee - Central_Park
    addEdge(34, 35); // Central_Park - City_Centre
    addEdge(35, 36); // City_Centre - Bengal_Chemical
    addEdge(36, 37); // Bengal_Chemical - Salt_Lake_Sector_V

    // PURPLE LINE (nodes 38-44) 
    addEdge(38, 39); // Joka - Thakurpukur
    addEdge(39, 40); // Thakurpukur - Sakherbazar
    addEdge(40, 41); // Sakherbazar - Behala_Chowrasta
    addEdge(41, 42); // Behala_Chowrasta - Behala_Bazar
    addEdge(42, 43); // Behala_Bazar - Taratala
    addEdge(43, 44); // Taratala - Majerhat

    // ORANGE LINE (nodes 45-53)
    addEdge(45, 46); // Kavi_Subhash_OL - Satyajit_Ray
    addEdge(46, 47); // Satyajit_Ray - Kazi_Nazrul_Islam
    addEdge(47, 48); // Kazi_Nazrul_Islam - Hemanta_Mukhopadhyay
    addEdge(48, 49); // Hemanta_Mukhopadhyay - Beleghata
    addEdge(49, 50); // Beleghata - Phoolbagan_OL
    addEdge(50, 51); // Phoolbagan_OL - Sealdah_OL
    addEdge(51, 52); // Sealdah_OL - Esplanade_OL
    addEdge(52, 53); // Esplanade_OL - Howrah_Maidan_OL

    // YELLOW LINE (nodes 54-56)
    addEdge(54, 55); // Noapara_YL - Bagjola
    addEdge(55, 56); // Bagjola - Jai_Hind

    //  INTERCHANGE EDGES (cross-line transfers)
    addEdge(11, 29); // Esplanade: Blue <-> Green
    addEdge(11, 52); // Esplanade: Blue <-> Orange
    addEdge(29, 52); // Esplanade: Green <-> Orange
    addEdge(25, 45); // Kavi_Subhash: Blue <-> Orange
    addEdge(26, 53); // Howrah_Maidan: Green <-> Orange
    addEdge(30, 51); // Sealdah: Green <-> Orange
    addEdge(31, 50); // Phoolbagan: Green <-> Orange
    addEdge(2,  54); // Noapara: Blue <-> Yellow
    string stations[N] = {
        // Blue Line (0-25)
        "Dakshineswar",
        "Baranagar",
        "Noapara",
        "Dum_Dum",
        "Belgachhia",
        "Shyambazar",
        "Shobhabazar_Sutanuti",
        "Girish_Park",
        "MG_Road",
        "Central",
        "Chandni_Chowk",
        "Esplanade(Blue)",
        "Park_Street",
        "Maidan",
        "Rabindra_Sadan",
        "Netaji_Bhavan",
        "Jatin_Das_Park",
        "Kalighat",
        "Rabindra_Sarobar",
        "Mahanayak_Uttam_Kumar",
        "Netaji",
        "Masterda_Surya_Sen",
        "Gitanjali",
        "Kavi_Nazrul",
        "Shahid_Khudiram",
        "Kavi_Subhash(Blue)",
        // Green Line (26-37)
        "Howrah_Maidan(Green)",
        "Howrah",
        "Mahakaran",
        "Esplanade(Green)",
        "Sealdah(Green)",
        "Phoolbagan(Green)",
        "SV_Marg",
        "Karunamoyee",
        "Central_Park",
        "City_Centre",
        "Bengal_Chemical",
        "Salt_Lake_Sector_V",
        // Purple Line (38-44)
        "Joka",
        "Thakurpukur",
        "Sakherbazar",
        "Behala_Chowrasta",
        "Behala_Bazar",
        "Taratala",
        "Majerhat",
        // Orange Line (45-53)
        "Kavi_Subhash(Orange)",
        "Satyajit_Ray",
        "Kazi_Nazrul_Islam",
        "Hemanta_Mukhopadhyay",
        "Beleghata",
        "Phoolbagan(Orange)",
        "Sealdah(Orange)",
        "Esplanade(Orange)",
        "Howrah_Maidan(Orange)",
        // Yellow Line (54-56)
        "Noapara(Yellow)",
        "Bagjola",
        "Jai_Hind"
    };

    int source;
    cout << "===== KOLKATA METRO - DIJKSTRA'S ALGORITHM =====" << endl;
    cout << "\nStation List:" << endl;
    for (int i = 0; i < N; i++)
        cout << "  " << i << "\t" << stations[i] << endl;

    cout << "\nEnter source station number: ";
    cin >> source;

    if (source < 0 || source >= N)
    {
        cout << "Invalid station number!" << endl;
        return 1;
    }

    dijkstra(graph, source, stations);
    return 0;
}
