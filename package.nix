{
  meson,
  ninja,
  stdenv,
}:
stdenv.mkDerivation {
  pname = "unity-single-instance-fix";
  version = "1.0.0";

  src = ./.;

  nativeBuildInputs = [
    meson
    ninja
  ];

  mesonFlags = [
    "--buildtype=debugoptimized"
  ];
}
