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

void free_recursion(rbtree *t, node_t *x){
  if(x == t->nil){
    return;
  }

  free_recursion(t, x->left);
  free_recursion(t, x->right);
  free(x);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  // RB tree 구조체가 차지했던 메모리 반환
  // 해당 tree가 사용했던 메모리를 전부 반환해야 합니다. (valgrind로 나타나지 않아야 함)
  //node_t *current = t->root;

  free_recursion(t, t->root);
  free(t->nil);
  t->nil = NULL; //댕글링 안 되게
  free(t);
  t = NULL; //댕글링 안 되게
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
  }else{ //x가 부모의 오른쪽 서브트리였다면
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
  }else{ //x가 부모의 오른족 서브트리였다면
    x->parent->right = y; //y로 연결
  }
  y->right = x; //왼쪽 노드의 오른쪽을 x로 연결
  x->parent = y; //y가 x를 자식으로 가졌으니, x의 부모는 y
}

void RB_INSERT_FIXUP(rbtree *t, node_t *z){
  while(z->parent->color == RBTREE_RED){ //삽입 노드의 부모가 red일 동안 (red가 연속되는 동안)
    if(z->parent == z->parent->parent->left){ //x의 부모가 할아버지의 왼쪽 서브트리였을 경우
      node_t *y = z->parent->parent->right; //y = 부모의 형제 = 삼촌
      if(y->color == RBTREE_RED){ //삼촌이 RED일 경우 = Case1
        z->parent->color = RBTREE_BLACK; 
        y->color = RBTREE_BLACK;        
        z->parent->parent->color = RBTREE_RED; //Case1: 부모&삼촌 = BLACK, 할아버지 = RED로 바꾸고
        z = z->parent->parent;          //할아버지에서 다시 확인
      }else{ //삼촌이 BLACK일 경우 = Case2 or Case3
        if(z == z->parent->right){ //z의 부모가 왼쪽 서브트리인데, z가 부모의 오른쪽 서브트리면 = 꺾여있는 상태 = Case2
          z = z->parent; 
          left_rotation(t, z); //z 기준 left로 rotation해서 Case3 적용 가능 상태로 바꿔줌
        }
        //Case3: 부모와 할아버지의 색을 바꾼 후, 할아버지 기준으로 회전
        //근데 조건에서 부모가 RED일 경우 while문을 도니까, 할아버지는 RED로 지정
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotation(t, z->parent->parent);
      }
    }else{ //z의 부모가 할아버지의 오른쪽 서브트리였을 경우 (위 코드에서 left <-> right)
      node_t *y = z->parent->parent->left;
      if(y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }else{
        if(z == z->parent->left){
          z = z->parent;
          right_rotation(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotation(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
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
    if(insert_node->key < current->key){ //multiset이니까 중복된 값 허용 = 어느쪽도 상관없음
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
  }else if(insert_node->key < insert_parent->key){ //삽입된 위치가 왼쪽이라면
    insert_parent->left = insert_node; //부모의 왼쪽 자식이 됨
  }else{ //삽입된 위치가 오른쪽이라면
    insert_parent->right = insert_node; //부모의 오른쪽 자식이 됨
  }
  insert_node->left = t->nil;
  insert_node->right = t->nil;
  insert_node->color = RBTREE_RED;
  RB_INSERT_FIXUP(t, insert_node); //RB-Tree 속성 확인&재구조 함수

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  // RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
  // 해당하는 node가 없으면 NULL 반환
  // segmentation 오류가 남 -> 확인해보니까 while문 돌릴 때 cur->key가 key가 아닐동안 도는데
  // 만약 key가 아예 없었다면, while문 계속 돌겠지... 종료조건 cur이 nil이 되면 종료되도록 추가해줌
  // 그럴거면 그냥 cur != t->nil일 동안 while문 도는 게 나은가
  // node_t *current = t->root;

  // while(current->key != key){
  //   if(current == t->nil){
  //     break;
  //   }

  //   if(key < current->key){
  //     current = current->left;
  //   }else{
  //     current = current->right;
  //   }
  // }

  // if(current == t->nil){
  //   return NULL;
  // }else{
  //   return current;
  // }

  if(t->root == t->nil){
    return NULL;
  }

  node_t *current = t->root;

  while(current != t->nil){
    if(key < current->key){
      current = current->left;
    }else if(key > current->key){
      current = current->right;
    }else{
      return current;
    }
  }

  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  // RB-tree 중 최솟값을 가진 node pointer 반환
  // RB-tree가 BST 기반이니까 가장 왼쪽 노드가 최솟값
  if(t->root == t->nil){ //tree가 비어있는 상태
    return NULL;
  }

  if(t->root->left == t->nil && t->root->right == t->nil){ //root 노드밖에 없는 상태
    return t->root;
  }
  
  node_t *current = t->root;


  while(current->left != t->nil){ //왼쪽 자식이 nil일 때까지 반복 = leaf 노드까지 감
    current = current->left;
  }

  return current;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  // RB-tree 중 최댓값을 가진 node pointer 반환
  // RB-tree가 BST 기반이니까 가장 오른쪽 노드가 최댓값
  if(t->root == t->nil){ //tree가 비어있는 상태
    return NULL;
  }

  if(t->root->left == t->nil && t->root == t->nil){ //root 노드밖에 없는 상태
    return t->root;
  }

  node_t *current = t->root;

  while(current->right != t->nil){ //오른쪽 자식이 nil일 때까지 반복 = leaf 노드까지 감
    current = current->right;
  }

  return current;
  //return t->root;
}

node_t *rb_minimum(rbtree *t, node_t *x){
  //successor 찾는 함수 (x가 삭제하려는 노드의 오른쪽 자녀)
  while (x->left != t->nil)
  {
    x = x->left;
  }
  return x;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v){
  // u에 자리에 v가 대체되는 함수
  if(u->parent == t->nil){ //교체되는 노드가 root였을 경우
    t->root = v; //v가 root
  }else if(u == u->parent->left){ //교체되는 노드가 왼쪽 서브트리였을 경우
    u->parent->left = v; 
  }else{ //교체되는 노드가 오른쪽 서브트리 였을 경우
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void RB_DELETE_FIXUP(rbtree *t, node_t *x){
  node_t *y;
  //형제가 null일 경우 예외처리를 해줘야 ㅎㅏ나...;;

  while(x != t->root && x->color == RBTREE_BLACK){
    if(x == x->parent->left){ //삭제되는 노드가 왼쪽 서브트리였을 경우
      y = x->parent->right; //형제 노드 저장
      if(y->color == RBTREE_RED){ //형제 노드가 RED일 경우 -> Case1
        //Case1: 부모&형제의 색을 바꾸고 부모 기준으로 회전(형제 노드를 Black으로 만들어서 Case 2/3/4 따질 수 있도록)
        y->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotation(t, x->parent);
        y = x->parent->right; //rotation 돌렸으니까 형제 재설정
      }
      //형제 노드가 BLACK일 경우 -> Case2 or Case3
      if(y->left->color == RBTREE_BLACK && y->right->color == RBTREE_BLACK){ //형제의 두 자녀 모두 BLACK일 경우 -> Case2
        //삭제노드의 Black과 형제의 Black을 부모에게 전달한 후 부모에서 해결하도록 위임
        y->color = RBTREE_RED;
        x = x->parent; //그래서 해결할 x는 부모가 됨
      }
      else{ //형제가 BLACK인 상태에서, 형제의 두 자녀 중 한 개는 RED인 상태
        if(y->right->color == RBTREE_BLACK){ //형제의 왼쪽 자녀: BLACK, 오른쪽 자녀: RED일 경우 -> Case3
          //Case3: 꺾인 상태니까 형제와 형제 자녀 중 RED인 자녀의 색을 바꾼 후 형제 기준 rotate 
          y->left->color = RBTREE_BLACK; //RED인 자녀 색 BLACK
          y->color = RBTREE_RED; //형제 색 BLACK
          right_rotation(t, y);
          y = x->parent->right; //rotation 돌렸으니까 형제 재설정
        }
        //펴줬으니까 Case4 적용 가능 상태
        //Case4: 형제=부모의 색, RED인 형제의 자녀=BLACK, 부모=BLACK으로 바꾼 후 부모를 기준으로 회전
        y->color = x->parent->color;
        y->right->color = RBTREE_BLACK;
        x->parent->color = RBTREE_BLACK;
        left_rotation(t, x->parent);
        x = t->root; //??
      }
    }else{ //삭제되는 노드가 오른쪽 서브트리였을 경우
      y = x->parent->left;
      if(y->color == RBTREE_RED){
        y->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotation(t, x->parent);
        y = x->parent->left;
      }
      if(y->left->color == RBTREE_BLACK && y->right->color == RBTREE_BLACK){
        y->color = RBTREE_RED;
        x = x->parent;
      }
      else{
        if(y->left->color == RBTREE_BLACK){
          y->right->color = RBTREE_BLACK;
          y->color = RBTREE_RED;
          left_rotation(t, y);
          y = x->parent->left;
        }
        y->color = x->parent->color;
        y->left->color = RBTREE_BLACK;
        x->parent->color = RBTREE_BLACK;
        right_rotation(t, x->parent);
        x = t->root; //??
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  // RB tree 내부의 p로 지정된 node를 삭제하고 메모리 반환
  node_t *y = p; //삭제하는 노드의 주소 값
  node_t *x; //삭제되는 노드를 대체하는 노드 저장

  color_t delete_color = y->color; //삭제되는 색 저장

  if(p->left == t->nil){            //삭제하는 노드의 왼쪽 자식이 없다면(자식이 한 개라면)
    x = p->right;                   //삭제하는 노드의 오른쪽 자식 저장
    rb_transplant(t, p, p->right);  //오른쪽 자식을 삭제하는 노드의 자리로 교체
    if(x == t->nil){ //만약 삭제되는 노드의 자식이 둘 다 없다면 여기로 들어옴
      t->nil->parent = NULL; //그럼 자식이 nil인데 transplant 하니까 nil의 parent가 설정되어버림, 그러니까 nil로 설정해주기
    }
  }else if(p->right == t->nil){     //삭제하는 노드의 오른쪽 자식이 없다면(자식이 한 개라면)
    x = p->left;                    //삭제되는 노드의 왼쪽 자식 저장ß
    rb_transplant(t, p, p->left);   //왼쪽 자식을 삭제하는 노드의 자리로 교체
  }else{ //삭제하는 노드의 자식이 두 개라면
    y = rb_minimum(t, p->right); //삭제되는 노드는 successor가 됨
    delete_color = y->color;  //삭제되는 색도 successor의 색
    x = y->right;
    if(y->parent == p){ //successor가 p의 오른쪽 노드일 경우
      x->parent = y; //x의 부모를 y로
    }else{
      rb_transplant(t, y, y->right);
      //p 위치에 successor인 y로 교체하기 전, y의 자리에 y자식을 교체 시켜두기
      //이 과정을 거쳐야, y가 자식을 달지 않은 상태로(y를 parent로 가지는 노드가 없는) z 위치에 이식될 수 있음
      y->right = p->right; //p의 오른쪽 자식을 y한테 달기
      y->right->parent = y; //쌍방 부모/자식 관계 형성
    }
    rb_transplant(t, p, y); //p 위치를 y로 교체
    y->left = p->left; //p의 왼쪽 자식을 y한테 달기
    y->left->parent = y; //쌍방 부모/자식 관계 형성
    y->color = p->color; //결과: y가 z자리로 가고 y는 z의 색만 물려 받음
  }
  // 삭제되는 색이 BLACK이었다면, black_height 속성이 깨지니까 균형을 맞춰줘야 함 (재구조)
  if(delete_color == RBTREE_BLACK){
    if(x != t->nil) // 삭제하는 노드를 대체하는 애가 nil이 아닐 때에만 재구조
                    // 대체되는 노드가 nil일 경우엔 재구조가 필요하지 않음 
      RB_DELETE_FIXUP(t, x);
  }
  free(p);
  return 0;
}

void inorder_tree(node_t *root, node_t *nil, key_t *arr, int *index, const size_t n){
  if(root == nil){
    return;
  }
  inorder_tree(root->left, nil, arr, index, n);
  if(*index < n){
    arr[*index] = root->key;
    printf("%d ", arr[*index]);
    (*index)++;
  }
  inorder_tree(root->right, nil, arr, index, n);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  // RB tree의 내용을 *key 순서대로* 주어진 array로 변환 //오름차순-중위순회//
  // array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
  // array의 메모리 공간은 이 함수를 부르는 쪽에서 준비하고 그 크기를 n으로 알려줍니다.
  //size_t: 객체나 값이 포함할 수 있는 최대 크기의 데이터를 표현하는 타입으로, 부호없는 정수형이지만 실제 데이터형은 아님

  int index = 0;
  inorder_tree(t->root, t->nil, arr, &index, n);
  printf("\n");

  return 0;
}

