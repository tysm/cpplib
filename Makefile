clean:
	$(RM) cpplib.pdf
	$(RM) .latex/cpplib.aux
	$(RM) .latex/cpplib.out
	$(RM) .latex/cpplib.log
	$(RM) .latex/cpplib.pdf
	$(RM) .latex/cpplib.tex
	$(RM) .latex/cpplib.toc
	find -name '*.out' -delete

format:
	find -name '*.cpp' -o -name '*.hpp' -o -name '*.c' -o -name '*.h' \
		| xargs clang-format-10 -i

pdf: clean
	$(SHELL) -c './cpplibtex'

test:
	$(SHELL) -c 'cd test; ./libtest.sh'

.PHONY: clean format pdf test
