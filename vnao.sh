###
# Copyright (C) 2016 Nicolas A. Ortega
# License: GNU GPLv3
###
#!/bin/bash
astyle --style=attach \
    --indent=spaces=4 \
    --indent-switches \
    --indent-labels \
    --indent-preproc-define \
    --indent-col1-comments \
    --pad-oper \
    --unpad-paren \
    --align-pointer=name \
    --add-brackets \
    --break-after-logical \
    --lineend=linux \
    source/*.cpp \
    source/*.h \
    includes/*.h

rm -rf src/client/*.orig src/server/*.orig src/*.orig src/gui/*.orig src/comp/*.orig src/sys/*.orig

echo "I CAN'T READ THAT CODE!!!"
