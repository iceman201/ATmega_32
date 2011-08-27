all: docs


docs:
	doxygen doxygen.config


zip: ucfk3.zip


ucfk3.zip: html/*
	zip -r $@ html/

clean:
	rm -r html
