CC = g++
CFLAGS = -O2
LFLAGS = -s
PROG1 = bin/countries.cgi
PROG2 = bin/convert
OBJS1 = obj/countries.o obj/main.o
OBJS2 = obj/countries.o obj/convert.o
HDRS = src/countries.hpp
DIRS = bin obj

all: $(PROG1) $(PROG2)

obj/%.o: src/%.cpp $(HDRS)
	$(CC) -o $@ $(CFLAGS) -c $<

$(PROG1): $(OBJS1)
	$(CC) $(LFLAGS) -o $@ $^ -lcgicc

$(PROG2): $(OBJS2)
	$(CC) $(LFLAGS) -o $@ $^

install:
	sudo -u apache -g apache cp -R jpg /srv/httpd/htdocs/countries/
	sudo -u apache -g apache cp src/countries.html /srv/httpd/htdocs
	bin/convert
	sudo -u apache -g apache cp countries.dat /srv/httpd/cgi-bin
	sudo -u apache -g apache cp bin/countries.cgi /srv/httpd/cgi-bin

.PHONY : clean
clean:
	$(RM) -rf $(PROG1) $(PROG2) obj bin src/*~ src/.*~ src/*.swp

$(shell mkdir -p $(DIRS))
