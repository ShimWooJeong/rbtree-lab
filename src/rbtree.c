#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  //nil은 빈 노드를 나타냄
  //color만 black으로 할당해주고 나머지는 NULL로 할당해주기
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
  nil_node->color = RBTREE_BLACK;
  nil_node->key = 0;
  nil_node->parent = NULL;
  nil_node->left = NULL;
  nil_node->right = NULL;

  //해당 함수는 rbtree의 기반을 다지는 함수 느낌?
  //노드도 없고 걍 nil만 있는 상태
  p->root = nil_node;
  p->nil = nil_node;
  
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *insert_node = (node_t*)malloc(sizeof(node_t)); 
  insert_node->color = RBTREE_RED; //삽입은 무조건 RED로
  insert_node->parent = t->nil;
  insert_node->left = t->nil;
  insert_node->right = t->nil;
  insert_node->key = key;

  node_t *insert_parent = t->nil;
  node_t *current = t->root;

  while(current != t->nil){ //삽입은 leaf 노드에서 이뤄지니까 leaf가 될 때까지 반복
    insert_parent = current; //while문 끝나면 current=nil이 되니까, nil로 옮겨지기 전 current를 저장, 즉 얘가 삽입될 위치의 부모가 됨
    if(key <= current->key){ //multiset이니까 중복된 값 허용 = 어느쪽도 상관없음
      current = current->left;
    }else{
      current = current->right;
    }
  }
  insert_node->parent = insert_parent; //삽입할 위치에서 부모 연결
  //자식이 부모를 가졌으면, 부모의 자식도 설정해줘야 함
  if(insert_parent == t->nil){ //삽입할 위치의 부모가 nil이었다, 그럼 root가 되어야 함
    t->root = insert_node;
    insert_node->color = RBTREE_BLACK; //root가 되면 black이 되어야 함
  }else if(key < insert_parent->key){ //삽입된 위치가 왼쪽이라면
    insert_parent->left = insert_node; //부모의 왼쪽 자식이 됨
  }else if(key > insert_parent->key){ //삽입된 위치가 오른쪽이라면
    insert_parent->right = insert_node; //부모의 오른쪽 자식이 됨
  }
  //RB_INSERT_FIXUP(t, insert_node); //RB-Tree 속성 확인&재구조 함수

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

void left_rotation(rbtree *t, node_t *x){
  node_t *y = x->right; //오른쪽 노드를 저장하는 temp 역할
  
  x->right = y->left; //해당 노드와 오른쪽 노드의 왼쪽 자식 연결

  if(y->left != t->nil){ //연결한 자식이 nil이 아니라면
    y->left->parent = x; //parent를 x로 설정
  }
  //nil은 존재하지 않는 가상의 노드로, 트리의 끝을 나타내기 위한 것
  //그러니까 부모를 설정하는 것은 무의미함


  y->parent = x->parent; //y의 부모를 x의 부모로 설정

  if(x->parent == t->nil){ //x가 root였다면
    t->root = y; //y가 root가 됨
  }else if (x == x->parent->left){ //x가 부모의 왼쪽 서브트리였다면
    x->parent->left = y; //y로 연결 
  }else if (x == x->parent->right){ //x가 부모의 오른쪽 서브트리였다면
    x->parent->right = y; //y로 연결
  }
  y->left = x; //오른쪽 노드의 왼쪽을 x로 연결
  x->parent = y; //y가 x를 자식으로 가졌으니, x의 부모는 y
}

void right_rotation(rbtree *t, node_t *x){
  node_t *y = x->left; //왼쪽 노드를 저장하는 temp 역할

  x->left = y->right; //해당 노드와 왼쪽 노드의 오른쪽 자식 연결

  if(y->right != t->nil){ //연결한 자식이 nil이 아니라면
    y->right->parent = x;
  }

  y->parent = x->parent; //y의 부모를 x의 부모로 설정

  if(x->parent == t->nil){ //x가 root였다면
    t->root = y; //y가 root가 됨
  }else if(x == x->parent->left){ //x가 부모의 왼쪽 서브트리였다면
    x->parent->left = y; //y로 연결
  }else if(x == x->parent->right){ //x가 부모의 오른족 서브트리였다면
    x->parent->right = y; //y로 연결
  }
  y->right = x; //왼쪽 노드의 오른쪽을 x로 연결
  x->parent = y; //y가 x를 자식으로 가졌으니, x의 부모는 y
}

int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();
    rbtree_insert(t, 10);
    rbtree_insert(t, 5);
    rbtree_insert(t, 30);
    // rbtree_insert(t, 45);
    // rbtree_insert(t, 25);
    // rbtree_insert(t, 35);
    //left_rotation(t, t->root);
    right_rotation(t, t->root);

    printf("root 값: %d\n", t->root->key);
    printf("right 값: %d\n", t->root->right->key);
    printf("right->right값: %d\n", t->root->right->right->key);
    // printf("right 값: %d\n", t->root->right->key);
    // printf("right->right값: %d\n", t->root->right->right->key);
    // printf("right->left값: %d\n", t->root->right->left->key);
    // printf("right->right->left값: %d\n", t->root->right->right->left->key);
}