.PHONY: help build test

help:
# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -E '^[a-zA-Z0-9_%/-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

build:
build: ## Build executables
	$(MAKE) -C src
#src 디렉토리의 Makefile을 실행 (별도로 지정하지 않았으니 전체 실행)

test:
test: ## Test rbtree implementation
	$(MAKE) -C test test
#test 디렉토리의 Makefile에서, test 명령어를 실행해라
	
clean:
clean: ## Clear build environment
	$(MAKE) -C src clean
#src 디렉토리의 Makefile에서, clean 명령어를 실행해라
	$(MAKE) -C test clean
#test 디렉토리의 Makefile에서, clean 명령어를 실행해라
