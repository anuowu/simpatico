BLD_DIR_REL =../..
include $(BLD_DIR_REL)/config.mk
include $(SRC_DIR)/tools/patterns.mk
include $(SRC_DIR)/tools/tests/sources.mk

TEST=$(BLD_DIR)/tools/tests/Test

.Secondary: $(tools_tests_OBJS)

all: $(tools_tests_EXES)

run: $(TEST)
	$(TEST) $(SRC_DIR)/tools/tests/ 

quiet: $(TEST)
	$(TEST) $(SRC_DIR)/tools/tests/ > log
	@echo `grep failed log` ", "\
              `grep successful log` "in tools/tests/log" > count
	@cat count

clean:
	rm -f $(tools_tests_OBJS) 
	rm -f $(tools_tests_OBJS:.o=.d)
	rm -f $(tools_tests_OBJS:.o=)
	rm -f log count
ifeq ($(BLD_DIR),$(SRC_DIR))
	cd chemistry; $(MAKE) clean
	cd config; $(MAKE) clean
	cd neighbor; $(MAKE) clean
	cd storage; $(MAKE) clean
	cd processor; $(MAKE) clean
	rm -f */*.o */*.d
#	$(MAKE) clean-outputs
#else
#	cd $(SRC_DIR)/tools/tests; $(MAKE) clean outputs
endif

#clean-outputs:
#	cd chemistry; $(MAKE) clean-outputs
        
-include $(tools_tests_OBJS:.o=.d)
-include $(tools_OBJS:.o=.d)
-include $(simp_OBJS:.o=.d)
-include $(util_OBJS:.o=.d)

