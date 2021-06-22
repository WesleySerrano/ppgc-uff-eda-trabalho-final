// typedefs for defining the adaptor
typedef CGAL::Exact_predicates_inexact_constructions_kernel                  K;
typedef CGAL::Delaunay_triangulation_2<K>                                    DelaunayTriangulation;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DelaunayTriangulation>                 AdaptationTraits;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DelaunayTriangulation> AP;
typedef CGAL::Voronoi_diagram_2<DelaunayTriangulation,AdaptationTraits,AP>                      CGAL_VoronoiDiagram;

// typedef for the result type of the point location
typedef AdaptationTraits::Site_2                    site2D;
typedef AdaptationTraits::Point_2                   point2D;
typedef CGAL_VoronoiDiagram::Locate_result             Locate_result;
typedef CGAL_VoronoiDiagram::Vertex_handle             Vertex_handle;
typedef CGAL_VoronoiDiagram::Face_handle               Face_handle;
typedef CGAL_VoronoiDiagram::Halfedge_handle           Halfedge_handle;
typedef CGAL_VoronoiDiagram::Ccb_halfedge_circulator   Ccb_halfedge_circulator;