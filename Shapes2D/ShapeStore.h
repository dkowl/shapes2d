#pragma once
#include "List.h"
#include "ShapeWizard.h"

namespace Shapes2D {

	template<typename TFloat>
	class ShapeStore {

		class ListNode;

		typedef List<ListNode> ShapeList;

		ShapeList list;

	public:	

		void AddShape(ShapeType shapeType) {
			list.Add(ListNode(ShapeWizard<TFloat>::CreateShape(shapeType), shapeType));
		}

		void DeleteShape(const ListNode& shape) {
			list.Delete(shape);
		}

		void DisplayShapes() {
			for (auto&& node : list) {
				node.shape->Display();
			}
		}

		const ShapeList& GetShapeList() {
			return list;
		}

		class ListNode {
		public:

			Shape<TFloat> *shape;
			ShapeType shapeType;
			int id;

			ListNode(Shape<TFloat> *shape, ShapeType shapeType) :
				shape(shape),
				shapeType(shapeType),
				id(GetNextId())
			{
			}

			bool operator==(const ListNode &other) const {
				return id == other.id;
			}

		private:

			static int GetNextId() {
				static int id = -1;
				id++;
				return id;
			}
		};		
	};
}

