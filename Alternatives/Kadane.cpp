#include <iostream>
using namespace std;

void printKadane(int arr[], int length) {
    int island_one = 0;
    int island_two = 0;
    int river = 0;
    int champion = 0;
    int phase = 1;
    
    for (int i = 0; i < length; i++) {
        // first island
        if (phase == 1) {
            if (arr[i] >= 0) {
                island_one = island_one + arr[i];
            } else if (arr[i] < 0) {
                river += arr[i];
                phase = 2;
            }
        // river
        } else if (phase == 2) {
            if (arr[i] <= 0) {
                river += arr[i];
            } else if (arr[i] > 0) {
                island_two = 0;
                island_two += arr[i];
                phase = 3;
            }
        // second island
        } else if (phase == 3) {
           if (arr[i] >= 0) {
                island_two =+ arr[i];
            } else if (arr[i] < 0) {
                if (island_one >= abs(river)) {
                    if (island_two >= abs(river)) {
                        island_one = island_one + island_two + river;
                        champion = max(champion, island_one);
                    } else {
                        champion = max(champion, island_one);
                        island_one = island_two;
                    }
                } else {
                    if (island_two >= abs(river)) {
                        island_one = island_two;
                        champion = max(champion, island_one);
                    } else {
                        island_one = island_two;
                        champion = max(max(champion, island_two), champion);
                    }
                }
                phase = 2;
                river = arr[i];
                island_two = 0;
            } 
        }
    } 
    // else we compute last values after exiting loop
    // check if isles are both 0!
    if (island_one >= abs(river)) {
        if (island_two >= abs(river)) {
            island_one = island_one + island_two + river;
            champion = max(champion, island_one);
        } else {
            champion = max(champion, island_one);
            island_one = island_two;
        }
    } else {
        if (island_two >= abs(river)) {
            island_one = island_two;
            champion = max(champion, island_one);
        } else {
            island_one = island_two;
            champion = max(max(island_one, island_two), champion);
        }
    }
    // print correct value
    // case limit: no positives
    if (island_one == island_two && island_one == 0) {
        int max = arr[0];
        for (int j = 1; j < length; j++) {
            if (arr[j] > max) {
                max = arr[j];
            }
        }
        cout << max << '\n';
    }
    else {
        cout << max(champion, island_one);
        cout << '\n';
    }
}