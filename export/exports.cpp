#include <windows.h>

#define MAP_EXPORTS(TRANSFORMER)                                                                                       \
    TRANSFORMER(1, "AddIPAddress")                                                                                     \
    TRANSFORMER(2, "AllocateAndGetArpEntTableFromStack")                                                               \
    TRANSFORMER(3, "AllocateAndGetIfTableFromStack")                                                                   \
    TRANSFORMER(4, "AllocateAndGetIpAddrTableFromStack")                                                               \
    TRANSFORMER(5, "AllocateAndGetIpForwardTableFromStack")                                                            \
    TRANSFORMER(6, "AllocateAndGetIpNetTableFromStack")                                                                \
    TRANSFORMER(7, "AllocateAndGetTcpExTableFromStack")                                                                \
    TRANSFORMER(8, "AllocateAndGetTcpTableFromStack")                                                                  \
    TRANSFORMER(9, "AllocateAndGetUdpTableFromStack")                                                                  \
    TRANSFORMER(10, "CancelIPChangeNotify")                                                                            \
    TRANSFORMER(11, "CancelMibChangeNotify2")                                                                          \
    TRANSFORMER(12, "ConvertGuidToStringA")                                                                            \
    TRANSFORMER(13, "ConvertGuidToStringW")                                                                            \
    TRANSFORMER(14, "ConvertInterfaceAliasToLuid")                                                                     \
    TRANSFORMER(15, "ConvertInterfaceGuidToLuid")                                                                      \
    TRANSFORMER(16, "ConvertInterfaceIndexToLuid")                                                                     \
    TRANSFORMER(17, "ConvertInterfaceLuidToAlias")                                                                     \
    TRANSFORMER(18, "ConvertInterfaceLuidToGuid")                                                                      \
    TRANSFORMER(19, "ConvertInterfaceLuidToIndex")                                                                     \
    TRANSFORMER(20, "ConvertInterfaceLuidToNameA")                                                                     \
    TRANSFORMER(21, "ConvertInterfaceLuidToNameW")                                                                     \
    TRANSFORMER(22, "ConvertInterfaceNameToLuidA")                                                                     \
    TRANSFORMER(23, "ConvertInterfaceNameToLuidW")                                                                     \
    TRANSFORMER(24, "ConvertLengthToIpv4Mask")                                                                         \
    TRANSFORMER(25, "ConvertStringToGuidW")                                                                            \
    TRANSFORMER(26, "CreateIpForwardEntry")                                                                            \
    TRANSFORMER(27, "CreateIpNetEntry")                                                                                \
    TRANSFORMER(28, "CreateProxyArpEntry")                                                                             \
    TRANSFORMER(29, "CreateSortedAddressPairs")                                                                        \
    TRANSFORMER(30, "DeleteIPAddress")                                                                                 \
    TRANSFORMER(31, "DeleteIpForwardEntry")                                                                            \
    TRANSFORMER(32, "DeleteIpNetEntry")                                                                                \
    TRANSFORMER(33, "DeleteProxyArpEntry")                                                                             \
    TRANSFORMER(34, "EnableRouter")                                                                                    \
    TRANSFORMER(35, "FlushIpNetTable")                                                                                 \
    TRANSFORMER(36, "FlushIpNetTableFromStack")                                                                        \
    TRANSFORMER(37, "FreeMibTable")                                                                                    \
    TRANSFORMER(38, "GetAdapterIndex")                                                                                 \
    TRANSFORMER(39, "GetAdapterOrderMap")                                                                              \
    TRANSFORMER(40, "GetAdaptersAddresses")                                                                            \
    TRANSFORMER(41, "GetAdaptersInfo")                                                                                 \
    TRANSFORMER(42, "GetBestInterface")                                                                                \
    TRANSFORMER(43, "GetBestInterfaceEx")                                                                              \
    TRANSFORMER(44, "GetBestInterfaceFromStack")                                                                       \
    TRANSFORMER(45, "GetBestRoute")                                                                                    \
    TRANSFORMER(46, "GetBestRoute2")                                                                                   \
    TRANSFORMER(47, "GetBestRouteFromStack")                                                                           \
    TRANSFORMER(48, "GetExtendedTcpTable")                                                                             \
    TRANSFORMER(49, "GetExtendedUdpTable")                                                                             \
    TRANSFORMER(50, "GetFriendlyIfIndex")                                                                              \
    TRANSFORMER(51, "GetIcmpStatisticsEx")                                                                             \
    TRANSFORMER(52, "GetIcmpStatistics")                                                                               \
    TRANSFORMER(53, "GetIcmpStatsFromStack")                                                                           \
    TRANSFORMER(54, "GetIfEntry")                                                                                      \
    TRANSFORMER(55, "GetIfEntry2")                                                                                     \
    TRANSFORMER(56, "GetIfEntry2Ex")                                                                                   \
    TRANSFORMER(57, "GetIfEntryFromStack")                                                                             \
    TRANSFORMER(58, "GetIfTable")                                                                                      \
    TRANSFORMER(59, "GetIfTable2")                                                                                     \
    TRANSFORMER(60, "GetIfTable2Ex")                                                                                   \
    TRANSFORMER(61, "GetIfTableFromStack")                                                                             \
    TRANSFORMER(62, "GetIgmpList")                                                                                     \
    TRANSFORMER(63, "GetInterfaceInfo")                                                                                \
    TRANSFORMER(64, "GetIpAddrTable")                                                                                  \
    TRANSFORMER(65, "GetIpAddrTableFromStack")                                                                         \
    TRANSFORMER(66, "GetIpForwardTable")                                                                               \
    TRANSFORMER(67, "GetIpForwardTable2")                                                                              \
    TRANSFORMER(68, "GetIpForwardTableFromStack")                                                                      \
    TRANSFORMER(69, "GetIpInterfaceTable")                                                                             \
    TRANSFORMER(70, "GetIpNetTable")                                                                                   \
    TRANSFORMER(71, "GetIpNetTable2")                                                                                  \
    TRANSFORMER(72, "GetIpNetTableFromStack")                                                                          \
    TRANSFORMER(73, "GetIpStatisticsEx")                                                                               \
    TRANSFORMER(74, "GetIpStatistics")                                                                                 \
    TRANSFORMER(75, "GetIpStatsFromStack")                                                                             \
    TRANSFORMER(76, "GetNetworkParams")                                                                                \
    TRANSFORMER(77, "GetNumberOfInterfaces")                                                                           \
    TRANSFORMER(78, "GetPerAdapterInfo")                                                                               \
    TRANSFORMER(79, "GetRTTAndHopCount")                                                                               \
    TRANSFORMER(80, "GetTcp6Table")                                                                                    \
    TRANSFORMER(81, "GetTcp6Table2")                                                                                   \
    TRANSFORMER(82, "GetTcpStatisticsEx")                                                                              \
    TRANSFORMER(83, "GetTcpStatistics")                                                                                \
    TRANSFORMER(84, "GetTcpStatsFromStack")                                                                            \
    TRANSFORMER(85, "GetTcpTable")                                                                                     \
    TRANSFORMER(86, "GetTcpTable2")                                                                                    \
    TRANSFORMER(87, "GetTcpTableFromStack")                                                                            \
    TRANSFORMER(88, "GetUdp6Table")                                                                                    \
    TRANSFORMER(89, "GetUdpStatisticsEx")                                                                              \
    TRANSFORMER(90, "GetUdpStatistics")                                                                                \
    TRANSFORMER(91, "GetUdpStatsFromStack")                                                                            \
    TRANSFORMER(92, "GetUdpTable")                                                                                     \
    TRANSFORMER(93, "GetUdpTableFromStack")                                                                            \
    TRANSFORMER(94, "GetUnicastIpAddressEntry")                                                                        \
    TRANSFORMER(95, "GetUnicastIpAddressTable")                                                                        \
    TRANSFORMER(96, "GetUniDirectionalAdapterInfo")                                                                    \
    TRANSFORMER(97, "Icmp6CreateFile")                                                                                 \
    TRANSFORMER(98, "Icmp6SendEcho2")                                                                                  \
    TRANSFORMER(99, "IcmpCloseHandle")                                                                                 \
    TRANSFORMER(100, "IcmpCreateFile")                                                                                 \
    TRANSFORMER(101, "IcmpParseReplies")                                                                               \
    TRANSFORMER(102, "IcmpSendEcho2Ex")                                                                                \
    TRANSFORMER(103, "IcmpSendEcho2")                                                                                  \
    TRANSFORMER(104, "IcmpSendEcho")                                                                                   \
    TRANSFORMER(105, "if_indextoname")                                                                                 \
    TRANSFORMER(106, "if_nametoindex")                                                                                 \
    TRANSFORMER(107, "InternalCreateIpForwardEntry")                                                                   \
    TRANSFORMER(108, "InternalCreateIpNetEntry")                                                                       \
    TRANSFORMER(109, "InternalDeleteIpForwardEntry")                                                                   \
    TRANSFORMER(110, "InternalDeleteIpNetEntry")                                                                       \
    TRANSFORMER(111, "InternalGetIfTable")                                                                             \
    TRANSFORMER(112, "InternalGetIpAddrTable")                                                                         \
    TRANSFORMER(113, "InternalGetIpForwardTable")                                                                      \
    TRANSFORMER(114, "InternalGetIpNetTable")                                                                          \
    TRANSFORMER(115, "InternalGetTcpTable")                                                                            \
    TRANSFORMER(116, "InternalGetUdpTable")                                                                            \
    TRANSFORMER(117, "InternalSetIfEntry")                                                                             \
    TRANSFORMER(118, "InternalSetIpForwardEntry")                                                                      \
    TRANSFORMER(119, "InternalSetIpNetEntry")                                                                          \
    TRANSFORMER(120, "InternalSetIpStats")                                                                             \
    TRANSFORMER(121, "InternalSetTcpEntry")                                                                            \
    TRANSFORMER(122, "IpReleaseAddress")                                                                               \
    TRANSFORMER(123, "IpRenewAddress")                                                                                 \
    TRANSFORMER(124, "IsLocalAddress")                                                                                 \
    TRANSFORMER(125, "NhGetGuidFromInterfaceName")                                                                     \
    TRANSFORMER(126, "NhGetInterfaceNameFromGuid")                                                                     \
    TRANSFORMER(127, "NhpAllocateAndGetInterfaceInfoFromStack")                                                        \
    TRANSFORMER(128, "NhpGetInterfaceIndexFromStack")                                                                  \
    TRANSFORMER(129, "NotifyAddrChange")                                                                               \
    TRANSFORMER(130, "NotifyIpInterfaceChange")                                                                        \
    TRANSFORMER(131, "NotifyRouteChange")                                                                              \
    TRANSFORMER(132, "NotifyRouteChange2")                                                                             \
    TRANSFORMER(133, "NotifyRouteChangeEx")                                                                            \
    TRANSFORMER(134, "NotifyUnicastIpAddressChange")                                                                   \
    TRANSFORMER(135, "ParseNetworkString")                                                                             \
    TRANSFORMER(136, "_PfAddFiltersToInterface@24")                                                                    \
    TRANSFORMER(137, "_PfAddGlobalFilterToInterface@8")                                                                \
    TRANSFORMER(138, "_PfBindInterfaceToIPAddress@12")                                                                 \
    TRANSFORMER(139, "_PfBindInterfaceToIndex@16")                                                                     \
    TRANSFORMER(140, "_PfCreateInterface@24")                                                                          \
    TRANSFORMER(141, "_PfDeleteInterface@4")                                                                           \
    TRANSFORMER(142, "_PfDeleteLog@0")                                                                                 \
    TRANSFORMER(143, "_PfGetInterfaceStatistics@16")                                                                   \
    TRANSFORMER(144, "_PfMakeLog@4")                                                                                   \
    TRANSFORMER(145, "_PfRebindFilters@8")                                                                             \
    TRANSFORMER(146, "_PfRemoveFilterHandles@12")                                                                      \
    TRANSFORMER(147, "_PfRemoveFiltersFromInterface@20")                                                               \
    TRANSFORMER(148, "_PfRemoveGlobalFilterFromInterface@8")                                                           \
    TRANSFORMER(149, "_PfSetLogBuffer@28")                                                                             \
    TRANSFORMER(150, "_PfTestPacket@20")                                                                               \
    TRANSFORMER(151, "_PfUnBindInterface@4")                                                                           \
    TRANSFORMER(152, "SendARP")                                                                                        \
    TRANSFORMER(153, "SetAdapterIpAddress")                                                                            \
    TRANSFORMER(154, "SetBlockRoutes")                                                                                 \
    TRANSFORMER(155, "SetIfEntry")                                                                                     \
    TRANSFORMER(156, "SetIfEntryToStack")                                                                              \
    TRANSFORMER(157, "SetIpForwardEntry")                                                                              \
    TRANSFORMER(158, "SetIpForwardEntryToStack")                                                                       \
    TRANSFORMER(159, "SetIpMultihopRouteEntryToStack")                                                                 \
    TRANSFORMER(160, "SetIpNetEntry")                                                                                  \
    TRANSFORMER(161, "SetIpNetEntryToStack")                                                                           \
    TRANSFORMER(162, "SetIpRouteEntryToStack")                                                                         \
    TRANSFORMER(163, "SetIpStatistics")                                                                                \
    TRANSFORMER(164, "SetIpStatsToStack")                                                                              \
    TRANSFORMER(165, "SetIpTTL")                                                                                       \
    TRANSFORMER(166, "SetPerTcpConnectionEStats")                                                                      \
    TRANSFORMER(167, "SetProxyArpEntryToStack")                                                                        \
    TRANSFORMER(168, "SetRouteWithRef")                                                                                \
    TRANSFORMER(169, "SetTcpEntry")                                                                                    \
    TRANSFORMER(170, "SetTcpEntryToStack")                                                                             \
    TRANSFORMER(171, "UnenableRouter")

FARPROC originals[171] = {};

[[maybe_unused]] static const auto init = []() {
    char dll_path[MAX_PATH];
    GetSystemDirectory(dll_path, sizeof(dll_path));

    strcat_s(dll_path, "\\IPHLPAPI.dll");
    auto *const original = LoadLibrary(dll_path);

#define LOAD_ORIGINAL(index, name) originals[(index)-1] = GetProcAddress(original, name);
    MAP_EXPORTS(LOAD_ORIGINAL)

    return true;
}();

#define EXPORT_FUNC(index, name)                                                                                       \
    extern "C" __attribute__((naked, stdcall)) void __ORIGINAL_EXPORT_##index##__()                                    \
    {                                                                                                                  \
        asm volatile("jmp *%0" : : "r"(originals[(index)-1]));                                                         \
    }

MAP_EXPORTS(EXPORT_FUNC)