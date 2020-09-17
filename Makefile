
all:
	(cd cmd && make)
	(cd margarita_gubanova-hw01 && make)
	(cd plugins/car_control && make)

clean:
	(cd cmd && make clean)
	(cd margarita_gubanova-hw01 && make clean)
	(cd plugins/car_control && make clean)

.PHONY: all clean
