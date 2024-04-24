.PHONY: clean
#실제 clean 파일이 존재하지 않더라도, make clean 명령어를 실행 가능하도록

CFLAGS=-Wall -g
#컴파일러 옵션
# -Wall: 모든 경고 활성화
# -g: 디버깅 정보 포함

driver: driver.o rbtree.o
# driver.o와 rbtree.o 파일을 링크해 driver라는 실행파일을 만듬

clean:
	rm -f driver *.o
# make clean 명령어 실행시 driver 실행 파일과 .o 확장자를 가진 모든 파일 삭제

# 이 Makefile은 'make' 명령을 사용해 빌드할 때 'driver' 실행파일을 생성하고
# 'make clean' 명령을 사용해 임시 파일 및 생성된 실행 파일을 정리한다