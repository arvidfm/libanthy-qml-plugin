Name:       libanthy-qml-plugin

# >> macros
# << macros

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    Bridge between QML and Anthy
Version:    0.1
Release:    1
License:    LGPLv2
URL:        https://github.com/BeholdMyGlory/libanthy-qml-plugin
Source0:    %{name}-%{version}.tar.gz
Requires: anthy
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(anthy)
#BuildRequires:  desktop-file-utils

%description
QML plugin that lets you talk to Anthy
from QML.


# %define debug_package %{nil}


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qtc_qmake5

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
# << install post

#desktop-file-install --delete-original       \
#  --dir %{buildroot}%{_datadir}/applications             \
#   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
/usr/lib/qt5/qml/se/behold/anthy/libjollaanthyplugin.so
/usr/lib/qt5/qml/se/behold/anthy/qmldir
# >> files
# << files
