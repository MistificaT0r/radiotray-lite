#
# spec file for package radiotray-lite
#

Name:           radiotray-lite
Version:        0.2.19
Release:        2
Summary:        Online radio streaming player with minimum interface
License:        GPL-3.0+
Group:          Productivity/Multimedia/Sound/Players
URL:            https://github.com/MistificaT0r/radiotray-lite
Source:         %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  fdupes
BuildRequires:  file-devel
BuildRequires:  gcc-c++
BuildRequires:  hicolor-icon-theme
BuildRequires:  pkgconfig
BuildRequires:  update-desktop-files
BuildRequires:  pkgconfig(appindicator3-0.1) >= 12.10
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gstreamer-1.0)
BuildRequires:  pkgconfig(gstreamermm-1.0)
BuildRequires:  pkgconfig(gtk+-3.0)
BuildRequires:  pkgconfig(gtkmm-3.0)
BuildRequires:  pkgconfig(libcurl)
BuildRequires:  pkgconfig(libnotify)
BuildRequires:  pkgconfig(libxml-2.0)
Recommends:     gstreamer-plugins-base
Recommends:     gstreamer-plugins-good
Recommends:     gstreamer-plugins-ugly
Recommends:     gstreamer-plugins-libav
Recommends:     gstreamer-transcoder

%description
Radio Tray Lite is a lightweight clone of the original Radio Tray online
radio streaming player rewritten in C++...

%prep
%setup -q

%build
%cmake
make %{?_smp_mflags}

%install
%cmake_install
%fdupes %{buildroot}%{_datadir}

%files
%doc LICENSE.md README.md
%{_bindir}/radiotray-lite
%{_datadir}/applications/radiotray-lite.desktop
%{_datadir}/pixmaps/radiotray-lite.png
%{_datadir}/radiotray-lite/

%changelog
* Fri Dec 02 2022 mistificat0r - 0.2.19-2
- Release with @thekvs latest commits f1da589.
