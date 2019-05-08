LIBS = -lreadline
all:
	gcc -g -o middaycommanderV0 v0/midday.c $(LIBS)
	gcc -g -o middaycommanderV1 v1/midday.c v1/helpers.c $(LIBS)
	gcc -g -o middaycommanderV2 v2/midday.c v2/helpers.c $(LIBS)
mc0:
	gcc -g -o middaycommanderV0 v0/midday.c $(LIBS)
mc1:
	gcc -g -o middaycommanderV1 v1/midday.c v1/helpers.c $(LIBS)
mc2:
	gcc -g -o middaycommanderV2 v2/midday.c v2/helpers.c $(LIBS)
clean:
	$(RM) middaycommanderV0
	$(RM) middaycommanderV1
	$(RM) middaycommanderV2
