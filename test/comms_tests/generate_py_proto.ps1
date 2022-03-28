# BUILD THE PROJECT FIRST, BECAUSE IN ORDER TO USE GENERATED PYTHON FILES
# YOU NEED NANOPB FILES WHICH ARE DOWNLOADED TO .pio DIRECTORY ON BUILD
# Also remember to change the import in generated python files from
# import nanopb_pb2 as nanopb__pb2
# to 
# import proto.nanopb_pb2 as nanopb__pb2

$ProtoCDirectory = "../../.pio/libdeps/megaatmega2560/Nanopb/generator"
$GenerateProtoCommand = "$ProtoCDirectory/protoc -I../../protocols --python_out=. Chassis.proto" 

# Generate the files
Invoke-Expression $GenerateProtoCommand

# List the required dependencies
Remove-Item -LiteralPath "./proto" -Force -Recurse 2>$null

# Copy fresh dependencies from .pio directory
Get-ChildItem -Path "$ProtoCDirectory/proto" | Copy-Item -Destination "./proto" -Recurse -Container