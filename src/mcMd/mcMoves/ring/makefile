BLD_DIR_REL =../../..
include $(BLD_DIR_REL)/config.mk
include $(SRC_DIR)/mcMd/patterns.mk

all: $(mcMd_mcMoves_ring_OBJS)

clean:
	rm -f $(mcMd_mcMoves_ring_OBJS) $(mcMd_mcMoves_ring_OBJS:.o=.d)

clean-deps:
	rm -f $(mcMd_mcMoves_ring_OBJS:.o=.d)

-include $(mcMd_mcMoves_ring_OBJS:.o=.d)

