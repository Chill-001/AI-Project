void bfs(State cur,State f)
{
    queue<int> q;
    int statesPassed=0;
    q.push(cur);
    while (!q.empty())
    {
        cur = q.pop();
        statePassed++;
        if (cur==f) {
          cur.printBoard();
          printf("%d", statesPassed);
          return;
        }
        for (int i = 0; i < 4; i++) {
          q.push(cur.move(i));
        }
    }
}
