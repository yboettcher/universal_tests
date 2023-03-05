{
  description = "A very basic flake";

  inputs = {
    universal = {
      url = "github:stillwater-sc/universal/v3.68";
      flake = false;
    };
    mtl4 = {
      url = "github:simunova/mtl4";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, universal, mtl4 }:
  let
    pkgs = nixpkgs.legacyPackages."x86_64-linux";
  in
  {

    packages.x86_64-linux.universal = pkgs.stdenv.mkDerivation {
      name = "universal";
      nativeBuildInputs = [pkgs.cmake];

      src = universal;

      doCheck = true;

      cmakeFlags = [
        "-DBUILD_DEMONSTRATION=OFF"
      ];
    };

    packages.x86_64-linux.mtl4 = pkgs.stdenv.mkDerivation {
      name = "mtl4";
      nativeBuildInputs = [pkgs.cmake];
      buildInputs = [pkgs.boost];

      src = mtl4;

    };

    packages.x86_64-linux.test_universal = pkgs.stdenv.mkDerivation {
      name = "test_universal";
      nativeBuildInputs = [pkgs.cmake];
      buildInputs = [self.packages.x86_64-linux.universal self.packages.x86_64-linux.mtl4 pkgs.boost pkgs.eigen];

      src = ./.;

      doCheck = true;

      checkPhase = ''
        ctest -j12
      '';
    };

    packages.x86_64-linux.default = self.packages.x86_64-linux.test_universal;

    apps.x86_64-linux.default = {
      type = "app";
      program = "${self.packages.x86_64-linux.test_universal}/bin/universal_test";
    };

  };
}