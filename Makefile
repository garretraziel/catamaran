default:
	g++ main.cpp bot.cpp -lgloox -pthread -o "catamaran"

all:
	g++ main.cpp bot.cpp -lgloox -pthread -o "catamaran"

Release:
	g++ main.cpp bot.cpp -lgloox -pthread -o "catamaran"

Debug:
	g++ main.cpp bot.cpp -Wall -g -lgloox -pthread -o "catamaran"
