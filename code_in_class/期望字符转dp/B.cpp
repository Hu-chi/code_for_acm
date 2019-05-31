#include <iostream>
#include <cstdio>
#include <map>
#include <list>

using namespace std;

int cnt[101];
int rank1[101];
int rank2[101];
float rank[101];
float buff[101];
bool tag[101];
map<int, list<int>> record1;
map<int, list<int>> record2;
int k1, k2;

struct Rate {
    float rank;
    list<int> teams;
    Rate * next;
};
Rate * head = NULL;

float compRank(Rate * a, Rate * b) {
    return a->rank - b->rank;
}
bool cmp(const void * a, const void * b) {
    return *(int *)a > *(int *)b ? true : false;
}
void exchangeRank(Rate *a, Rate * b) {
    float rank = a->rank;
    list<int> teams = a->teams;
    a->rank = b->rank;
    a->teams = b->teams;
    b->rank = rank;
    b->teams = teams;
}
void sortRank() {
    if (head == NULL || head->next == NULL) {
        return;
    }
    Rate * key = head->next;
    Rate * p = head;
    while (key != NULL) {
        while (p != key) {
            if (compRank(p, key) > 0) {
                exchangeRank(p, key);
            }
            p = p->next;
        }
        p = head;
        key = key->next;
    }
}
void readData() {
    char buf[10000];
    int teamId;
    int teamCnt;
    char * pCur;
    int rankSum = 0;
    int rankCur = 0;

    gets(buf);
    sscanf(buf, "%d", &k1);
    for (int i = 0; i < k1; ++i) {
        gets(buf);
        rankCur = rankSum + 1;
        pCur = strtok(buf, " ");
        list<int> ts;
        while (pCur) {
            ++rankSum;
            teamId = atoi(pCur);
            ++cnt[teamId];
            rank1[teamId] = rankCur;
            ts.push_back(teamId);
            pCur = strtok(NULL, " ");
        }
        record1[rankCur] = ts;
    }
    getchar();
    gets(buf);
    sscanf(buf, "%d", &k2);
    rankSum = rankCur = 0;
    for (int i = 0; i < k2; ++i) {
        gets(buf);
        rankCur = rankSum + 1;
        pCur = strtok(buf, " ");
        list<int> ts;
        while (pCur) {
            ++rankSum;
            teamId = atoi(pCur);
            ++cnt[teamId];
            rank2[teamId] = rankCur;
            ts.push_back(teamId);
            pCur = strtok(NULL, " ");
        }
        record2[rankCur] = ts;
    }
}

void cc2() {
    for (int i = 1; i <= 100; ++i) {
        if (cnt[i] == 2) {
            rank[i] = rank1[i] + rank2[i];
        }
    }
    for (int i = 1; i <= 200; ++i) {
        Rate * rate = new Rate;
        rate->rank = i;
        for (int j = 1; j <= 100; ++j) {
            if (rank[j] == i) {
                rate->teams.push_back(j);
            }
        }
        if (!rate->teams.empty()) {
            rate->next = head;
            head = rate;
        }
    }
}

void cc1() {
    for (int i = 1; i <= 100; ++i) {
        if (cnt[i] != 1) {
            continue;
        }
        int r;
        int p;
        if (rank1[i] != 0) {
            r = rank1[i];
            p = 1;
        } else {
            r = rank2[i];
            p = 2;
        }
        int count = 0;
        list<int> temp;
        if (p == 1) {
            temp = record1[r];
        } else {
            temp = record2[r];
        }
        list<int> eq;
        for (list<int>::iterator it = temp.begin(); it != temp.end(); ++it) {
            if (cnt[*it] == 2) {
                eq.push_back(*it);
            }
        }
        if (!eq.empty()) {
            int rc = rank[eq.front()];
            bool flag = true;
            for (list<int>::iterator it = eq.begin(); it != eq.end(); ++it) {
                if (rank[*it] != rc) {
                    rank[i] = 0;
                    flag = false;
                    break;
                }
            }
            if (flag == true) {
                for (Rate * p = head; p != NULL; p = p->next) {
                    if (p->rank == rc) {
                        p->teams.push_back(i);
                        break;
                    }
                }
            }
        } else {
            tag[i] = true;
        }
    }
    for (int i = 1; i <= 100; ++i) {
        if (tag[i] != true) {
            continue;
        }
        int p;
        int r;
        if (rank1[i] != 0) {
            r = rank1[i];
            p = 1;
        } else {
            r = rank2[i];
            p = 2;
        }
        int * temp = (p == 1) ? rank1 : rank2;
        int prior = -1;
        int next = 101;
        for (int j = 1; j <= 100; ++j) {
            if (temp[j] != 0 && temp[j] < r && rank[j] != 0) {
                if (rank[j] > prior) {
                    prior = rank[j];
                }
            }
            if (temp[j] != 0 && temp[j] > r && rank[j] != 0) {
                if (rank[j] < next) {
                    next = rank[j];
                }
            }

        }
        if (next > prior) {
            buff[i] = (next + prior) / 2.0;
        }
    }
}

void insertcc1() {
    for (int i = 1; i <= 100; ++i) {
        if (buff[i] == 0) {
            continue;
        }
        float fr = buff[i];
        Rate * p = head;
        Rate * rate = new Rate;
        rate->rank = fr;
        rate->teams.push_back(i);
        if (head == NULL || fr < head->rank) {
            rate->next = head;
            head = rate;
            continue;
        } else if (fr == head->rank) {
            int t1 = rank1[i] > 0 ? rank1[i] :rank2[i];
            int t2 = rank1[head->teams.front()] > 0 ?rank1[head->teams.front()] : rank2[head->teams.front()];
            if (t1 == t2) {
                head->teams.push_back(i);
                continue;
            } else if (t1 < t2) {
                rate->next = head;
                head = rate;
                continue;
            }
        }
        Rate * q = p->next;
        bool f = false;
        while(q != NULL) {
            if (fr < q->rank) {
                rate->next = q;
                p->next = rate;
                f = true;
                break;
            } else if (fr == q->rank) {
                int t1 = rank1[i] > 0 ? rank1[i] :rank2[i];
                int t2 = rank1[q->teams.front()] > 0 ?rank1[q->teams.front()] : rank2[q->teams.front()];
                if (t1 == t2) {
                    q->teams.push_back(i);
                } else if (t1 < t2) {
                    rate->next = q;
                    p->next = rate;
                } else {
                    if (q->next == NULL) {
                        rate->next = q->next;
                        q->next = rate;
                    } else{
                        int t3 = rank1[q->next->teams.front()] > 0 ? rank1[q->next->teams.front()] : rank2[q->next->teams.front()];
                        if (t3 > t1) {
                            rate->next = q->next;
                            q->next = rate;
                        } else {
                            p = p->next;
                            q = q->next;
                            continue;
                        }
                    }
                }
                f = true;
                break;
            }
            p = p->next;
            q = q->next;
        }
        if (f == true) { continue; }
        rate->next = NULL;
        p->next = rate;
    }
}

void output() {
    for (Rate * p = head; p != NULL; p = p->next) {
        p->teams.sort();
        for (list<int>::iterator it = p->teams.begin(); it != p->teams.end(); ++it) {
            if (*it != p->teams.back()) {
                cout << *it << " ";
            } else {
                cout << *it;
                if (p->next != NULL) {
                    cout << endl;
                }
            }
        }
    }
}

int main () {
    readData();
    cc2();
    sortRank();
    cc1();
    insertcc1();
    output();
    system("pause");
    return 0;
}
