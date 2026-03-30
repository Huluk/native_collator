MAKEFLAGS += --always-make

build:
	flutter pub get

run:
	cd example && flutter run

unit_test:
	flutter test

integration_test:
	cd example && flutter test integration_test/

test: unit_test integration_test
