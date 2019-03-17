#/bin/bash

echo "Building testdata files using dasm..."

pushd testdata 1>/dev/null
for t in $(ls tests_*.asm); do
	testname=$(basename $t .asm)
	dasm $testname.asm -o$testname.out 1>/dev/null
done
popd 1>/dev/null

echo "Done."
echo "Generated files *.out should be added to git."
