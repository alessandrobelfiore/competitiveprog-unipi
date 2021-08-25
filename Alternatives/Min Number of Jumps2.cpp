int minJumps(int arr[], int n) {

  if (arr[0] == 0) return -1;

  int max = arr[0];
  int steps = arr[0];
  int jumps = 1;

  for (int i = 1; i < n; i++) {
    if (i == n - 1) return jumps;
    max = max > (i + arr[i]) ? max : (i + arr[i]);
    steps --;
    if (steps == 0) {
      jumps ++;
      if (i >= max) return -1;
      steps = max - i;
    }
  }
  return jumps;
}