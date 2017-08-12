Name:       darkstar3
Summary:    A darkstar3 solution
Version:    0.0.1
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dbus-glib-1 glib-2.0)
Requires(post): /sbin/ldconfig  
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A darkstar3 solution (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel



%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`  
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}  


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


#%files
#%{_libdir}/libcapi-network-nfc.so.0
#%{_libdir}/libcapi-network-nfc.so.0.0.1

#%files devel
#%{_includedir}/network/*.h
#%{_libdir}/pkgconfig/*.pc
#%{_libdir}/libcapi-network-nfc.so
