# Visuallisation of Methanogenesis

This application is was designed to aid in the visualisation of metabolic pathways. Data is provided in the form of a json in the data directory. Provided is a JSON describing the Kinetic Model of Methanogensis in _M. Acetivorens_. All rate constants and reaction data are derived from [this paper](https://www.hindawi.com/journals/archaea/2014/898453/) by _Peterson et. al._,

This project was developed in CLion and XCode. Provided is a CMake.txt for testing and debugging backend logic. To run the actual application use the [final-project-KatherineRitchie.xcodeproj]() file. Line 80 of ofApp.cpp must be modified to provide the filepath for the methanogenesis.json file from the users root directory.
