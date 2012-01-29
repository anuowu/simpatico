include $(SRC_DIR)/mcMd/potentials/pair/sources.mk
include $(SRC_DIR)/mcMd/potentials/bond/sources.mk

mcMd_potentials_SRCS=\
    $(mcMd_potentials_pair_SRCS) \
    $(mcMd_potentials_bond_SRCS) 

ifdef MCMD_ANGLE
include $(SRC_DIR)/mcMd/potentials/angle/sources.mk
mcMd_potentials_SRCS+=$(mcMd_potentials_angle_SRCS) 
endif

ifdef MCMD_DIHEDRAL
include $(SRC_DIR)/mcMd/potentials/dihedral/sources.mk
mcMd_potentials_SRCS+=$(mcMd_potentials_dihedral_SRCS) 
endif

ifdef MCMD_LINK
include $(SRC_DIR)/mcMd/potentials/link/sources.mk
mcMd_potentials_SRCS+=$(mcMd_potentials_link_SRCS) 
endif

ifdef MCMD_EXTERNAL
include $(SRC_DIR)/mcMd/potentials/external/sources.mk
mcMd_potentials_SRCS+=$(mcMd_potentials_external_SRCS) 
endif

ifdef MCMD_TETHER
include $(SRC_DIR)/mcMd/potentials/tether/sources.mk
mcMd_potentials_SRCS+=$(mcMd_potentials_tether_SRCS) 
endif

mcMd_potentials_OBJS=$(mcMd_potentials_SRCS:.cpp=.o)

