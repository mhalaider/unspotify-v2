# Unspotify v2

Spotify launcher and patcher for Windows platform. Currently only skipping the adverstiment tracks in Spotify Free version.

## Build

Clone repository from github
```bash
  git clone https://github.com/mhalaider/unspotify-v2
```
- Open the project "unspotify-v2.sln" file via Visual Studio 2022 or later.
- Select build type Release (no logs) or Debug.
- Press Ctrl+Shift+B or click in navigation **Build->"Build project"** button to compile project.

## Installation

After successful compilation you will need take a more few steps.

- Open Spotify path. By default it is "%APPDATA%\Spotify" (Win+R and paste this path).
- Copy the build files (launcher.exe and spot-module.dll in output folder) to opened path.
- Start launcher.exe (If nothing happens try start it via **admin** rights).
- Done! Enjoy it :)
