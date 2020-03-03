#!/bin/sh
# Usage: ./postprocess_doc.sh
set -ev

cd doc/jegp

# Link "[label]" in "C++ Standard's [label]" to "https://wg21.link/label".
find . -type f -exec sed -i "s/C++ Standard's \[\([a-z.]\+\?\)\]/C++ Standard's <a href=\"https:\/\/wg21.link\/\1\">[\1]<\/a>/g" {} \;

# Relink LaTeX source hidden links.
find . -type f -exec sed -i "s/doc\/source/doc/g" {} \;

# Remove unused indexes from `index.html`.
sed -i "s/<h2 ><a href='conceptindex'>Index of library concepts<\/a><\/h2><h2 ><a href='impldefindex'>Index of implementation-defined behavior<\/a><\/h2>//" index.html

# Use "Bare" internal links with .html extension for github.io MIME correctness.
mv contents contents.html
mv fig fig.html
mv footnotes footnotes.html
mv full full.html
mv generalindex generalindex.html
mv hash.combine hash.combine.html
mv headerindex headerindex.html
mv intro intro.html
mv intro.general intro.general.html
mv libraryindex libraryindex.html
mv refs refs.html
mv requirements requirements.html
mv reserved.names reserved.names.html
mv scope scope.html
mv static.downcast static.downcast.html
mv tab tab.html
mv utilities utilities.html
mv utilities.general utilities.general.html
mv utility utility.html
mv utility.syn utility.syn.html
mv utility.underlying utility.underlying.html
