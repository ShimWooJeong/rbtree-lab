.PHONY: test
# 타겟으로 작성한 이름과 디렉토리 내 파일 이름이 서로 같을 경우,
# 오작동을 방지하기 위해 .PHONY 사용

CFLAGS=-I ../src -Wall -g -DSENTINEL
# 컴파일 옵션
# -I: include 디렉토리 지정, 상위 디렉토리의 src 디렉토리를 포함
# -Wall: 모든 경고 표시
# -g: 디버깅 정보 포함
# -DSENTINE: SENTINEL이라는 매크로 상수 정의 -> 이를 통해 test-rbtree에 ifdef가 활성화됨

test: test-rbtree
	./test-rbtree
	valgrind ./test-rbtree
# 밑에 있는 test-rbtree 명령어로 test-rbtree 실행파일을 만들고,
# test-rbree 실행파일을 실행, valgrind 도구를 사용해 실행결과 검사함 (메모리 누수 및 관련 오류)
# 결국 우리가 make test를 해서 테스트 케이스를 돌려볼 때
# 이 test라는 타겟을 실행하기 위한 것

test-rbtree: test-rbtree.o ../src/rbtree.o
# test-rbtree.o와 ../src/rbtree.o를 링크해 실행파일 만듬

../src/rbtree.o:
	$(MAKE) -C ../src rbtree.o
# 명령어 실행시 의존성 파일을 생성하는 역할
# ../src 폴더에서 Makefile을 찾아서 rbtree.o를 빌드

clean:
	rm -f test-rbtree *.o
# Makefile에서 생성된 파일들을 삭제함