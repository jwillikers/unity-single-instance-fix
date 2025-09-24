default: build

alias b := build

build: setup
    meson compile -C build

alias ch := check

check: && format
    yamllint .
    asciidoctor *.adoc
    lychee --cache *.html
    nix flake check

alias s := setup

setup:
    meson setup --buildtype debugoptimized build

alias f := format
alias fmt := format

format:
    treefmt

package:
    nix build

alias u := update
alias up := update

update:
    nix run ".#update-nix-direnv"
    nix run ".#update-nixos-release"
    nix flake update
