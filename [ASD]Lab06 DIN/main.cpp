#include <iostream>
#include <cstring>

using namespace std;

struct node {
    char charL;
    char charR;
    int maxLeft;
    int maxRight;
    int max;
    char letter;
    int count;
    int prior;
    node *l, *r;
    bool rev;

    explicit node(char l) : letter(l), count(1), prior(rand()), l(nullptr),
                            r(nullptr),
                            maxLeft(1), maxRight(1), charL(l), charR(l), max(1),
                            rev(false) {}
};

typedef node *pnode;

//ilość węzłów w danym poddrzewie
int counter(pnode v) {
    return v ? v->count : 0;
}

//sprawdzenie, czy poddrzewo zawiera wszystkie identyczne litery
bool sameLetters(pnode v) {
    return v->maxLeft == v->maxRight && v->max == v->count &&
           v->maxLeft == v->max;
}

//odwrócenie informacji w wierzchołku
void changeIfInverted(pnode v) {
    if (v && v->rev) {
        swap(v->maxLeft, v->maxRight);
        swap(v->charL, v->charR);
    }
}

void updateSumsBothNull(pnode v) {
    v->charL = v->letter;
    v->charR = v->letter;
    v->maxLeft = v->maxRight = v->max = 1;
}

void updateSumsRightNull(pnode v) {
    v->charL = v->l->charL;
    v->charR = v->letter;
    v->maxLeft = v->l->maxLeft;
    v->maxRight = 1;

    if (v->l->charR == v->letter && sameLetters(v->l)) {
        v->maxLeft = v->maxRight = v->max = v->l->max + 1;
    } else if (v->l->charR == v->letter) {
        v->maxRight += v->l->maxRight;
        v->max = max(v->l->max, v->maxRight);
    } else {
        v->max = v->l->max;
    }
}

void updateSumsLeftNull(pnode v) {
    v->charR = v->r->charR;
    v->charL = v->letter;
    v->maxRight = v->r->maxRight;
    v->maxLeft = 1;

    if (v->r->charL == v->letter && sameLetters(v->r)) {
        v->maxLeft = v->maxRight = v->max = v->r->max + 1;
    } else if (v->r->charL == v->letter) {
        v->maxLeft += v->r->maxLeft;
        v->max = max(v->r->max, v->maxLeft);
    } else {
        v->max = v->r->max;
    }
}

void updateSumsBothAlive(pnode v) {
    int maxEdges = max(v->l->max, v->r->max);
    v->charL = v->l->charL;
    v->charR = v->r->charR;
    v->maxLeft = v->l->maxLeft;
    v->maxRight = v->r->maxRight;

    if (v->l->charR == v->letter && sameLetters(v->l) &&
        v->r->charL == v->letter && sameLetters(v->r)) {
        v->maxLeft = v->maxRight = v->max = v->l->max + 1 + v->r->max;

    } else if (v->l->charR == v->letter && sameLetters(v->l) &&
               v->r->charL == v->letter) {
        v->maxLeft += 1 + v->r->maxLeft;
        v->max = max(v->maxLeft, v->r->max);

    } else if (v->l->charR == v->letter && sameLetters(v->l)) {
        v->maxLeft += 1;
        v->max = max(v->maxLeft, v->r->max);

    } else if (v->l->charR == v->letter && v->r->charL == v->letter &&
               sameLetters(v->r)) {
        v->maxRight += v->l->maxRight + 1;
        v->max = max(v->l->max, v->maxRight);

    } else if (v->r->charL == v->letter && sameLetters(v->r)) {
        v->maxRight += 1;
        v->max = max(v->l->max, v->maxRight);

    } else if (v->l->charR == v->letter && v->r->charL == v->letter) {
        v->max = max(v->l->maxRight + 1 + v->r->maxLeft, maxEdges);

    } else if (v->r->charL == v->letter) {
        v->max = max(1 + v->r->maxLeft, maxEdges);

    } else if (v->l->charR == v->letter) {
        v->max = max(v->l->maxRight + 1, maxEdges);

    } else {
        v->max = maxEdges;
    }
}

//update'owanie sum
void updateSums(pnode v) {
    changeIfInverted(v->l);
    changeIfInverted(v->r);

    if (!v->r && !v->l) {
        updateSumsBothNull(v);
    } else if (!v->r) {
        updateSumsRightNull(v);
    } else if (!v->l) {
        updateSumsLeftNull(v);
    } else {
        updateSumsBothAlive(v);
    }

    changeIfInverted(v->l);
    changeIfInverted(v->r);
}

//wypychanie informacji o odwróceniu do dzieci
void push(pnode v) {
    if (v && v->rev) {
        v->rev = false;
        swap(v->l, v->r);
        if (v->l) v->l->rev ^= true;
        if (v->r) v->r->rev ^= true;
    }
}

//update'owanie informacji o wierzchołku na podstawie dzieci
void update(pnode v) {
    if (!v) return;
    v->count = counter(v->l) + counter(v->r) + 1;
    updateSums(v);
}

void merge(pnode &t, pnode l, pnode r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    update(t);
}

void split(pnode t, pnode &l, pnode &r, int key, int add = 0) {
    if (!t)
        return void(l = r = nullptr);
    push(t);
    int cur_key = add + counter(t->l);
    if (key <= cur_key) {
        split(t->l, l, t->l, key, add);
        r = t;
    } else {
        split(t->r, t->r, r, key, add + 1 + counter(t->l));
        l = t;
    }
    update(t);
}

//operacja O
void invertDNA(pnode t, int start, int end) {
    pnode treeBehind, treeToReverse, treeAfter;
    split(t, treeBehind, treeToReverse, start - 1);
    split(treeToReverse, treeToReverse, treeAfter, end - start + 1);
    treeToReverse->rev ^= true;
    merge(t, treeBehind, treeToReverse);
    merge(t, t, treeAfter);
}

//operacja P
void deleteMoveDNA(pnode t, int start, int end, int newInd, int dnaSize) {
    if (start == newInd) {
        return;
    }

    int interval = end - start + 1;
    if (interval == dnaSize) {
        return;
    }

    pnode treeBehind, treeToMove, treeAfter, newTreeBehind, newTreeAfter;
    split(t, treeBehind, treeToMove, start - 1);
    split(treeToMove, treeToMove, treeAfter, interval);

    merge(t, treeBehind, treeAfter);
    split(t, newTreeBehind, newTreeAfter, newInd - 1);
    merge(t, newTreeBehind, treeToMove);
    merge(t, t, newTreeAfter);
}

//operacja N
int findBiggestSeq(pnode t, int start, int end) {
    int result;
    pnode treeBehind, TreeResult, treeAfter;
    split(t, treeBehind, TreeResult, start - 1);
    split(TreeResult, TreeResult, treeAfter, end - start + 1);
    result = TreeResult->max;
    merge(t, treeBehind, TreeResult);
    merge(t, t, treeAfter);
    return result;
}

//funkcja do zachowania porządku kopcowego
void heapify(pnode t) {
    if (!t) return;
    pnode max = t;
    if (t->l && t->l->prior > max->prior)
        max = t->l;
    if (t->r && t->r->prior > max->prior)
        max = t->r;
    if (max != t) {
        swap(t->prior, max->prior);
        heapify(max);
    }
}

//budowanie treapa
node *build(char *a, int n) {
    if (!n) return nullptr;
    int mid = n / 2;
    node *t = new node(a[mid]);
    t->l = build(a, mid);
    t->r = build(a + mid + 1, n - mid - 1);
    heapify(t);
    update(t);
    return t;
}


int main() {

    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string dna;

    cin >> n >> m;
    cin >> dna;

    int startInd, endInd, newInd = 0;
    char instr;

    char dnaArray[n + 1];
    strcpy(dnaArray, dna.c_str());
    node *tree = build(dnaArray, n);

    for (int i = 0; i < m; i++) {
        cin >> instr;
        cin >> startInd >> endInd;

        if (instr == 'O') {
            invertDNA(tree, startInd, endInd);

        } else if (instr == 'P') {
            cin >> newInd;
            deleteMoveDNA(tree, startInd, endInd, newInd, n);

        } else {
            cout << findBiggestSeq(tree, startInd, endInd) << "\n";
        }
    }
}
