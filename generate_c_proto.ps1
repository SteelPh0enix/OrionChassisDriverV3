# Change the include from "protocols/Chassis.pb.h" to "Chassis.pb.h" in Chassis.pb.c
python .pio/libdeps/megaatmega2560/Nanopb/generator/nanopb_generator.py "protocols/Chassis.proto" -D "./lib"

